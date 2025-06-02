#ifndef CALORIESCALCULATOR_H
#define CALORIESCALCULATOR_H

#include <Arduino.h>
#include "HeartRateMonitor.h"  // Needed for passing reference
#include "StepCounter.h"

class CaloriesCalculator {
public:
    // Adds interval kcal to running total and returns new total
    static void update(const HeartRateMonitor& hrMonitor, const StepCounter& stepCounte);

    // Resets total calories to 0
    static void resetTotal();

    // Returns total kcal burned
    static int getTotal();

private:
    // Estimate kcal burned in 1 minute using current heart rate
    static int calculatePerMinute(const HeartRateMonitor& hrMonitor);

    // Returns kcal burned for fixed interval
    static int calculateTotal(const HeartRateMonitor& hrMonitor);

    static int caloriesFromSteps(const StepCounter& stepCounter);

    static constexpr float userWeightKg = 90.0f;
    static constexpr int userAge = 22;
    static constexpr float intervalMinutes = 0.5f;
    static unsigned long lastCalcTime;
    static int totalCalories;
};

#endif // CALORIESCALCULATOR_H
