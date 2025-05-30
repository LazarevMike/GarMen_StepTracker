#include "CaloriesCalculator.h"

// Internal static variable to store total calories
int CaloriesCalculator::totalCalories = 0;

// Zillman formula (male version) to estimate kcal burned per minute
int CaloriesCalculator::calculatePerMinute(int heartRate, float weightKg, int age) {
    float numerator = -55.0969f + (0.6309f * heartRate) + (0.1988f * weightKg) + (0.2017f * age);
    float kcal = numerator / 4.184f;
    return static_cast<int>(kcal); // Rounded down (truncate)
}

// Multiply per-minute burn by number of minutes
int CaloriesCalculator::calculateTotal(int heartRate, float weightKg, int age, float minutes) {
    float kcal = calculatePerMinute(heartRate, weightKg, age) * minutes;
    return static_cast<int>(kcal); // Truncate to integer
}

// Update total calories with current interval and return new total
int CaloriesCalculator::updateTotalCalories(int heartRate, float weightKg, int age, float minutes) {
    int intervalKcal = calculateTotal(heartRate, weightKg, age, minutes);
    totalCalories += intervalKcal;
    return totalCalories;
}

// Reset stored total calories
void CaloriesCalculator::resetTotal() {
    totalCalories = 0;
}

// Accessor for current total
int CaloriesCalculator::getTotal() {
    return totalCalories;
}

// Public reset: resets all state variables (here: totalCalories)
void CaloriesCalculator::reset() {
    totalCalories = 0;
}
