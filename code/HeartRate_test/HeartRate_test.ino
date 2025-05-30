#include <Arduino.h>
#include "HeartRateMonitor.h"
#include "CaloriesCalculator.h"

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
    hrMonitor.update();

    // Every 30 seconds, update calorie burn
    unsigned long now = millis();
    if (now - lastCalcTime >= 30000) {
        lastCalcTime = now;

        int bpm = hrMonitor.getLatestBPM();
        float intervalKcal = CaloriesCalculator::calculateTotal(bpm, userWeightKg, userAge, 0.5f);
        float totalKcal = CaloriesCalculator::updateTotalCalories(bpm, userWeightKg, userAge, 0.5f);

        Serial.printf("BPM: %d | Interval: %.2f kcal | Total: %.2f kcal\n", bpm, intervalKcal, totalKcal);
    }

    delay(10); // Lightweight loop
}
