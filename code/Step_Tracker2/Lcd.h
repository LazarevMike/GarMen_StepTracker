#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <TFT_eSPI.h>  // Graphics library for TFT display
#include "StepCounter.h"
#include "HeartRateMonitor.h"
#include "CaloriesCalculator.h"

// Enum to track which screen is currently being displayed
enum class DisplayState {
    StepsScreen,  // Screen showing step data and pace
    StatsScreen   // Screen showing heart rate and calories
};

// Lcd class handles all screen-related logic and drawing
class Lcd {
public:
    // Constructor: accepts references to other modules
    Lcd(StepCounter& stepCounter, HeartRateMonitor& hrMonitor, CaloriesCalculator& calCalc);

    // Initializes the TFT screen
    void begin();

    // Switches to a new display state (StepsScreen or StatsScreen)
    void display(DisplayState newState);

private:
    // Gathers and updates current step data from StepCounter
    void setStepData();

    // Retrieves the latest BPM from HeartRateMonitor
    void setHeartRate();

    // Retrieves total burned calories from CaloriesCalculator
    void setCalories();

    // Updates the BLE connection status
    void bluetoothStatus();

    // Draws top UI bar: app name, BLE status, battery, time
    void drawCommonUI();

    // Switches between walk and idle state images
    void updateStateImage();

    // Renders the steps and pace screen
    void showStepsScreen();

    // Renders the heart rate and calorie stats screen
    void showStatsScreen();

    // Displays correct Bluetooth icon (connected or not)
    void bluetoothStateImage();

    // Renders battery icon based on a simulated percentage
    void batteryLevel();

    // -------------------- Member Variables --------------------

    DisplayState currentState;   // Tracks which screen is currently shown

    int stepCount;               // Current step count
    float stepsPerMinute;        // Steps per minute (pace)
    int bpm;                     // Heart rate in BPM
    int calories;                // Calories burned
    bool statusBLE;              // BLE connection status
    Pace pace;                   // Current user pace (IDLE, WALK, RUN)

    // References to other modules (no ownership)
    StepCounter& stepCounter;
    HeartRateMonitor& hrMonitor;
    CaloriesCalculator& calCalc;

    // For timing display switching and animations
    unsigned long lastSwitchTime;   // For animation/image switching
    unsigned long lastBatteryTime;  // For updating battery icon
    bool isRunning;                 // Toggles animation state (walk/idle)
};

#endif // LCD_H
