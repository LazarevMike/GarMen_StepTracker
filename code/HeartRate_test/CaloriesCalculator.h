#ifndef CALORIESCALCULATOR_H
#define CALORIESCALCULATOR_H

class CaloriesCalculator {
public:
    // Returns kcal burned in 1 minute at the given heart rate, weight (kg), and age
    static float calculatePerMinute(int heartRate, float weightKg, int age);

    // Returns kcal burned for a specific duration in minutes
    static float calculateTotal(int heartRate, float weightKg, int age, float minutes);

    // Adds interval kcal to running total and returns the new total
    static float updateTotalCalories(int heartRate, float weightKg, int age, float minutes);

    // Resets total to 0
    static void resetTotal();

    // Returns current total
    static float getTotal();
    
private:
    static float totalCalories;  // Accumulates over time
};

#endif // CALORIESCALCULATOR_H
