#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <TFT_eSPI.h> // Or appropriate display lib

// UI display mode controller for the screen
enum class DisplayState {
    StepsScreen,   // Step count and steps/min display
    StatsScreen    // Heart rate and calories display
};

class Lcd {
public:
    Lcd();

    void begin();                              // Initialize the screen
    void display(DisplayState newState);       // Trigger display redraw

    void setStepData(]);
    void setHeartRate();
    void setCalories();
    void bluetoothStatus();
    drawCommonUI();
}

private:
    DisplayState currentState;

    // Cached data for screen updates
    int stepCount;
    float stepsPerMinute;
    int bpm;
    int calories;
    bool statusBLE;
    // need to implement pace idk what type it should be

    // Screen handlers
    void showStepsScreen();
    void showStatsScreen();
};

#endif // LCD_H
