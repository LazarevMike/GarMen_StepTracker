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


}

void loop() {
  tft.setTextSize(2);
  tft.setCursor(105, 20);
  tft.print("GarMen");  // App title


  // should recieve this data type
  const char* axis = "-X";
  float xAxisValue = -0.14;
  float yAxisValue = -0.84;
  float zAxisValue = -3.58;

  tft.setTextSize(3);
  tft.setCursor(20, 80);
  tft.printf("Calib axis:%s", axis);

  tft.setTextSize(2);
  tft.setCursor(20, 140);
  tft.printf("X:%.2f", xAxisValue);

  tft.setCursor(100, 170);
  tft.printf("Y:%.2f", yAxisValue);

  tft.setCursor(180, 140);
  tft.printf("Z:%.2f", zAxisValue);

  delay(50);  // ~20Hz sampling
}
