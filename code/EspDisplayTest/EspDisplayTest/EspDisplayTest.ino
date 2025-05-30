#include <Adafruit_ST7789.h>
#include <math.h> // for sqrt

#include "whiterun_rgb565_fixed.h"
#include "idle_white_on_black_80x88.h"
#include "flame_icon.h"

// Display pins
#define TFT_CS   5
#define TFT_RST  6
#define TFT_DC   7

#define PIN_SELF_TEST 34
#define PIN_LED_BLUE  37

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// ADXL335 analog pins (IO13 is ADC2, IO8 and IO9 are ADC1)
#define ADXL_X 13
#define ADXL_Y 8
#define ADXL_Z 9

// Image position and size
const int maxImageWidth = 80;
const int maxImageHeight = 88;
const int yText = 20;
const int yImg = yText + 20;
const int xImg = (280 - maxImageWidth) / 2;

// Timers
unsigned long lastSwitchTime = 0;
unsigned long lastTimerUpdate = 0;
unsigned long elapsedSeconds = 0;
bool isRunning = true;

// Step counter
int steps = 0;
float prevMagnitude = 0;
unsigned long lastStepTime = 0;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // Full 12-bit resolution

  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);

  // Turn the LEDs ON
  digitalWrite(35, HIGH);
  digitalWrite(36, HIGH);
  digitalWrite(37, HIGH);

  tft.init(240, 280);
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);

  // Print title
  tft.setTextSize(2);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(false);
  const char* message = "GarMen";
  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(message, 0, 0, &x1, &y1, &w, &h);
  int xText = (tft.width() - w) / 2;
  tft.setCursor(xText, yText);
  tft.print(message);

  // Show initial running image
  tft.drawRGBBitmap(xImg, yImg, whiterun_img, 80, 82);

  // Score / Distance / SPM
  tft.setTextSize(4);
  tft.setCursor(80, 130);
  tft.print("00000");

  tft.setTextSize(2.5);
  tft.setCursor(100, 170);
  tft.print("/10000");

  tft.setTextSize(2);
  tft.setCursor(85, 200);
  tft.print("SPM ");

  tft.setCursor(130, 200);
  tft.print("2.5");

  tft.drawRGBBitmap(170, 197, flame_img, 19, 19);
}

void loop() {
  // --- IMAGE TOGGLING ---
  if (millis() - lastSwitchTime >= 5000) {
    lastSwitchTime = millis();
    isRunning = !isRunning;

    tft.fillRect(xImg, yImg, maxImageWidth, maxImageHeight, ST77XX_BLACK);

    if (isRunning) {
      tft.drawRGBBitmap(xImg, yImg, whiterun_img, 80, 82);
    } else {
      tft.drawRGBBitmap(xImg, yImg, idle_img, 80, 88);
    }
  }

  // --- TIMER DISPLAY ---
  if (millis() - lastTimerUpdate >= 1000) {
    lastTimerUpdate = millis();
    elapsedSeconds++;

    int hours = elapsedSeconds / 3600;
    int minutes = (elapsedSeconds % 3600) / 60;
    int seconds = elapsedSeconds % 60;

    char timerBuf[9];
    sprintf(timerBuf, "%02d:%02d:%02d", hours, minutes, seconds);

    tft.fillRect(5, 20, 80, 30, ST77XX_BLACK);
    tft.setTextSize(1);
    tft.setTextColor(ST77XX_WHITE);
    tft.setCursor(5, 20);
    tft.print("Timer");

    tft.setCursor(5, 30);
    tft.print(timerBuf);
  }

  // --- STEP COUNTER LOGIC ---
  int xRaw = analogRead(ADXL_X);
  int yRaw = analogRead(ADXL_Y);
  int zRaw = analogRead(ADXL_Z);

  float x = (float)xRaw;
  float y = (float)yRaw;
  float z = (float)zRaw;

  float magnitude = sqrt(x * x + y * y + z * z);

  float gain = 0.2;  // Sensitivity scaling
  float delta = (magnitude - prevMagnitude) * gain;

  if (delta > 10 && millis() - lastStepTime > 300) {
    steps++;
    lastStepTime = millis();

    Serial.print("Steps: ");
    Serial.println(steps);
  }

  prevMagnitude = magnitude;

  delay(50);  // ~20Hz sampling
}
