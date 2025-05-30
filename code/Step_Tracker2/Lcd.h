#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <TFT_eSPI.h>                    // TFT display library
#include "StepCounter.h"                 // Step tracking module
#include "HeartRateMonitor.h"           // BLE heart rate module
#include "CaloriesCalculator.h"         // Calorie calculation module

/*
   Enum representing the two main UI states of the screen:
   - StepsScreen: shows total steps, steps/min, and goal progress
   - StatsScreen: shows heart rate and calories burned
*/
enum class DisplayState {
    StepsScreen,
    StatsScreen
};

/*
   Lcd class manages UI rendering on the TFT screen.
   It displays real-time stats including steps, pace, heart rate, calories,
   and Bluetooth connection status.

   This class pulls data from StepCounter, HeartRateMonitor, and CaloriesCalculator.
*/
class Lcd {
public:
    /*
       Constructor that links this display class to the data providers.
       Takes references to:
       - stepCounter: step tracking logic
       - hrMonitor: BLE heart rate monitor
       - calCalc: calorie calculator
    */
    Lcd(StepCounter& stepCounter, HeartRateMonitor& hrMonitor, CaloriesCalculator& calCalc);

    // Initializes the TFT display (rotation, background, default text settings)
    void begin();

    // Switches screen state (StepsScreen or StatsScreen) and redraws if changed
    void display(DisplayState newState);

    // Fetches and stores step data: count, steps per minute, and pace
    void setStepData();

    // Retrieves current heart rate (BPM) from heart rate monitor
    void setHeartRate();

    // Retrieves total calories burned from calculator
    void setCalories();

    // Updates BLE connection status for display
    void bluetoothStatus();

    // Draws a top bar UI element with logo, BLE status, battery, and timer
    void drawCommonUI();

private:
    DisplayState currentState;  // Tracks which screen is currently shown

    // Cached values used for display rendering
    int stepCount;
    float stepsPerMinute;
    int bpm;
    int calories;
    bool statusBLE;
    Pace pace;  // Current detected pace (Idle, Walk, Run)

    // References to external data sources (passed in via constructor)
    StepCounter& stepCounter;
    HeartRateMonitor& hrMonitor;
    CaloriesCalculator& calCalc;

    // Renders the StepsScreen with step data
    void showStepsScreen();

    // Renders the StatsScreen with heart rate and calories
    void showStatsScreen();
};

#endif // LCD_H
