#include "ADXL335.h"
#include "UserInterface.h"
#include <Arduino.h>
#include "HeartRateMonitor.h"
#include "CaloriesCalculator.h"


ADXL335 adxl(8, 13, 9, 34);
UserInterface ui(35, 36, 37, 21, 26, 33);
unsigned int last_trigger = 0;
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;


HeartRateMonitor hrMonitor;
float totalCalories = 0.0f;
unsigned long lastCalcTime = 0;
const float userWeightKg = 90.0f;
const int userAge = 22;


void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("Starting BLE Heart Rate Monitor...");
    hrMonitor.begin();
}

void loop() {
  //ui.testLeds();
  ui.testButtons();  

  // Test Script for HR + Calories
  hrMonitor.update();
  // Every 30 seconds, update calorie burn
  unsigned long now = millis();
  if (now - lastCalcTime >= 30000) {
      lastCalcTime = now;

      int bpm = hrMonitor.getLatestBPM();
      float intervalKcal = CaloriesCalculator::calculateTotal(bpm, userWeightKg, userAge, 0.5f);
      float totalKcal = CaloriesCalculator::updateTotalCalories(bpm, userWeightKg, userAge, 0.5f);

      Serial.printf("BPM: %d | Interval: %d kcal | Total: %d kcal\n", bpm, intervalKcal, totalKcal);
  }

  delay(10); // Lightweight loop



  // //Serial.print("Current X: ");
  // Serial.print(-3.6);       // lower bound
  // Serial.print("\t");
  // Serial.print(3.6);    // upper bound
  // Serial.print("\t");
  // //Serial.print(adxl.readX());
  // Serial.print(adxl.convertADCtoAccel(adxl.readX()));
  // Serial.print("\t");
  // //Serial.print(adxl.readY());
  // Serial.print(adxl.convertADCtoAccel(adxl.readY()));
  // Serial.print("\t");
  // //Serial.println(adxl.readZ());
  // Serial.println(adxl.convertADCtoAccel(adxl.readZ()));

  // delay(50);

  // // if (millis() - last_trigger > 1000) {
  // //   adxl.triggerSt(!adxl.getStState());
  // //   last_trigger = millis();
  // // }

}
