#include "CaloriesCalculator.h"
#include <math.h>

// Initialize static member variables
unsigned long CaloriesCalculator::lastCalcTime = 0;
float CaloriesCalculator::totalCalories = 0.0f;

/*
   CaloriesCalculator class estimates total calories burned using either:
   - Heart rate (preferred, more accurate)
   - Step count and pace as fallback when HR monitor is disconnected
*/
float CaloriesCalculator::caloriesFromSteps(const StepCounter& stepCounter) {
    int spm = stepCounter.getStepsPerMinute();
    float kcalPerStep = 0.03f;

    switch (stepCounter.getPace()) {
        case WALK: kcalPerStep = 0.04f; break;
        case RUN:  kcalPerStep = 0.06f; break;
        default:   kcalPerStep = 0.03f; break;
    }

    float stepsInInterval = spm * intervalMinutes;
    return stepsInInterval * kcalPerStep;
}

/*
 * Calculates estimated kilocalories burned per minute using the heart rate.
 */
float CaloriesCalculator::calculatePerMinute(const HeartRateMonitor& hrMonitor) {
    int heartRate = hrMonitor.getLatestBPM();
    return fabsf(
        (-55.0969f + 0.6309f * heartRate + 0.1988f * userWeightKg + 0.2017f * userAge) / 4.184f
    );
}

/*
 * Calculates total calories burned over the fixed interval.
 */
float CaloriesCalculator::calculateTotal(const HeartRateMonitor& hrMonitor) {
    return calculatePerMinute(hrMonitor) * intervalMinutes;
}

/*
 * Periodically updates the total calories burned.
 */
void CaloriesCalculator::update(const HeartRateMonitor& hrMonitor, const StepCounter& stepCounter) {
    unsigned long now = millis();

    if (now - lastCalcTime >= 1000) {
        lastCalcTime = now;

        if (hrMonitor.isConnected()) {
            totalCalories += calculateTotal(hrMonitor);
        } else {
            totalCalories += caloriesFromSteps(stepCounter);
        }

        // Clamp to prevent negative values
        if (totalCalories < 0.0f) totalCalories = 0.0f;
    }
}

/*
 * Returns the total calories as a rounded integer.
 */
int CaloriesCalculator::getTotal() {
    return static_cast<int>(roundf(totalCalories));
}

/*
 * Resets the total calories count and restarts the update timer.
 */
void CaloriesCalculator::resetTotal() {
    totalCalories = 0.0f;
    lastCalcTime = millis();
}
