#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <math.h> // for sqrt

#define PIN_SELF_TEST 34
#define PIN_LED_BLUE  35

unsigned long lastTimerUpdate = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(PIN_SELF_TEST, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  static bool stState = false; // Static to preserve state across loops

if (millis() - lastTimerUpdate >= 1000) {
  lastTimerUpdate = millis();
 

  // Timer display (already exists)

  // Toggle ST and LED
  stState = !stState;
  //digitalWrite(PIN_SELF_TEST, stState ? HIGH : LOW);
  digitalWrite(PIN_LED_BLUE, stState ? HIGH : LOW);
}

}
