#ifndef LCD_H
#define LCD_H

#include <Arduino.h>
#include <TFT_eSPI.h>  // Graphics library for TFT display
#include <StepCounter.h> // For Pace enum

// Graphics and display libraries
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <math.h>

// Icons and images used on the display
#include "media/runIcon.h"
#include "media/walkIcon.h"
#include "media/idleIcon.h"
#include "media/flameIconSmall.h"
#include "media/heartIcon.h"
#include "media/bluetoothNotConnectedIcon.h"
#include "media/bluetoothConnectedIcon.h"
#include "media/flameIconBig.h"
#include "media/batteryIcon.h"

// Enum to track which screen is currently being displayed
enum class DisplayState {
    StepsScreen,  // Screen showing step data and pace
    StatsScreen,   // Screen showing heart rate and calories
    CalibScreen
};

// Lcd class handles all screen-related logic and drawing
class Lcd {
public:
    // Constructor: accepts references to other modules
    Lcd();

    // Initializes the TFT screen
    void begin();

    // Switches to a new display state (StepsScreen or StatsScreen)
    void display(DisplayState newState);

    // Gathers and updates current step data from StepCounter
    void setStepData(int newSteps, int newspm, Pace newPace);

    // Retrieves the latest BPM from HeartRateMonitor
    void setHeartRate(int newBPM);

    // Retrieves total burned calories from CaloriesCalculator
    void setCalories(int newCalories);

    // Updates the BLE connection status
    void setBluetoothStatus(bool newStatusBLE);

    //Update battery level
    void setBatteryLevel(int newBatteryPercentage);

private:
    static constexpr uint8_t REFRESH_HZ = 50;  // Refresh rate in Hz
    unsigned long lastRefreshTime = 0;

    GFXcanvas16 canvas;
    // Draws top UI bar: app name, BLE status, battery, time
    void drawCommonUI();

    // Switches between walk and idle state images
    void updateStateImage();

    // Renders the steps and pace screen
    void showStepsScreen();

    // Renders the heart rate and calorie stats screen
    void showStatsScreen();

    // Renders the calibration screen to start calibration
    void showCalibrationScreen();

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
    int batteryPercentage = 45;       // Current battery percentage (0 - 100)%


    // For timing display switching and animations
    unsigned long lastSwitchTime;   // For animation/image switching
    unsigned long lastBatteryTime;  // For updating battery icon
    bool isRunning;                 // Toggles animation state (walk/idle)
};

#endif // LCD_H
