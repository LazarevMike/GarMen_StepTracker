#include "CaloriesCalculator.h"

// Internal static variable to store total calories
float CaloriesCalculator::totalCalories = 0.0f;

// Zillman formula (male version) to estimate kcal burned per minute
float CaloriesCalculator::calculatePerMinute(int heartRate, float weightKg, int age) {
    float numerator = -55.0969f + (0.6309f * heartRate) + (0.1988f * weightKg) + (0.2017f * age);
    return numerator / 4.184f;
}

// Multiply per-minute burn by number of minutes
float CaloriesCalculator::calculateTotal(int heartRate, float weightKg, int age, float minutes) {
    return calculatePerMinute(heartRate, weightKg, age) * minutes;
}

// Update total calories with current interval and return new total
float CaloriesCalculator::updateTotalCalories(int heartRate, float weightKg, int age, float minutes) {
    float intervalKcal = calculateTotal(heartRate, weightKg, age, minutes);
    totalCalories += intervalKcal;
    return totalCalories;
}

// Reset stored total calories
void CaloriesCalculator::resetTotal() {
    totalCalories = 0.0f;
}

// Accessor for current total
float CaloriesCalculator::getTotal() {
    return totalCalories;
}
