#ifndef CALORIESCALCULATOR_H
#define CALORIESCALCULATOR_H

#include <Arduino.h>
#include "HeartRateMonitor.h"  // Needed for passing reference
#include "StepCounter.h"

class CaloriesCalculator {
public:
    // Adds interval kcal to running total and returns new total
    static void update(const HeartRateMonitor& hrMonitor, const StepCounter& stepCounter);

    // Resets total calories to 0
    static void resetTotal();

    // Returns total kcal burned
    static int getTotal();

private:
    // Estimate kcal burned in 1 minute using current heart rate
    static float calculatePerMinute(const HeartRateMonitor& hrMonitor);

    // Returns kcal burned for fixed interval
    static float calculateTotal(const HeartRateMonitor& hrMonitor);

    static float caloriesFromSteps(const StepCounter& stepCounter);

    static constexpr float userWeightKg = 90.0f;
    static constexpr int userAge = 22;
    static constexpr float intervalMinutes = 0.5f;
    static unsigned long lastCalcTime;
    static float totalCalories;
};

#endif // CALORIESCALCULATOR_H
