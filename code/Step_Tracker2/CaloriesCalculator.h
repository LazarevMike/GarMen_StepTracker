#ifndef CALORIESCALCULATOR_H
#define CALORIESCALCULATOR_H

class CaloriesCalculator {
public:
    // Returns kcal burned in 1 minute at the given heart rate, weight (kg), and age
    static int calculatePerMinute(int heartRate, float weightKg, int age);

    // Returns kcal burned for a specific duration in minutes
    static int calculateTotal(int heartRate, float weightKg, int age, float minutes);

    // Adds interval kcal to running total and returns the new total
    static int updateTotalCalories(int heartRate, float weightKg, int age, float minutes);

    // Resets total to 0
    static void resetTotal();

    // Returns current total
    static int getTotal();

    // Resets all internal state (e.g., total calories) to 0
    static void reset();

private:
    static int totalCalories;  // Accumulates over time as integer kcal
};

#endif // CALORIESCALCULATOR_H
