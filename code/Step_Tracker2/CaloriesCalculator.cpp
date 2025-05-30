#include "CaloriesCalculator.h"
#include <Arduino.h>

// Initialize static member variables
unsigned long CaloriesCalculator::lastCalcTime = 0;
int CaloriesCalculator::totalCalories = 0;

/*
 * Calculates estimated kilocalories burned per minute using the heart rate.
 * The formula is a simplified version of the calorie burn equation based on:
 *   kcal/min = (-55.0969 + 0.6309 * HR + 0.1988 * weight_kg + 0.2017 * age) / 4.184
 * The result is converted to a positive value using fabsf() and cast to int.
 */
int CaloriesCalculator::calculatePerMinute(const HeartRateMonitor& hrMonitor) {
    int heartRate = hrMonitor.getLatestBPM();
    float kcalPerMin = fabsf(
        (-55.0969f + 0.6309f * heartRate + 0.1988f * userWeightKg + 0.2017f * userAge) / 4.184f
    );
    return static_cast<int>(kcalPerMin);
}

/*
 * Calculates total calories burned over the fixed time interval (e.g. 0.5 min).
 * Multiplies the per-minute rate by the interval duration.
 */
int CaloriesCalculator::calculateTotal(const HeartRateMonitor& hrMonitor) {
    return calculatePerMinute(hrMonitor) * intervalMinutes;
}

/*
 * Periodically updates the total calories burned.
 * Only updates if 5 seconds have passed since the last update and the HR monitor is connected.
 */
void CaloriesCalculator::update(const HeartRateMonitor& hrMonitor) {
    unsigned long now = millis();

    // Update every 5 seconds and only when BLE HR device is connected
    if (now - lastCalcTime >= 5000 && hrMonitor.isConnected()) {
        lastCalcTime = now;
        totalCalories += calculateTotal(hrMonitor);
    }
}

/*
 * Returns the current total calories burned.
 */
int CaloriesCalculator::getTotal() {
    return totalCalories;
}

/*
 * Resets the total calories count and restarts the update timer.
 */
void CaloriesCalculator::resetTotal() {
    totalCalories = 0;
    lastCalcTime = millis();
}
