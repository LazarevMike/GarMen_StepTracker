#include "Lcd.h"
#include "Arduino.h"

#include <math.h>  // For future vector calculations, e.g., battery or pace indicators
#include "media/whiterun_rgb565_fixed.h"
#include "media/idle_white_on_black_80x88.h"
#include "media/flame_icon.h"

// Global TFT display instance
TFT_eSPI tft = TFT_eSPI();

/*
   Constructor: Initializes internal state for the display,
   stores references to external modules for sensor data access,
   and sets initial values for all UI elements.
*/
Lcd::Lcd(StepCounter& stepCounter, HeartRateMonitor& hrMonitor, CaloriesCalculator& calCalc)
    : currentState(DisplayState::StepsScreen),
      stepCount(0),
      stepsPerMinute(0),
      bpm(0),
      calories(0),
      statusBLE(false),
      pace(Pace::IDLE),
      stepCounter(stepCounter),
      hrMonitor(hrMonitor),
      calCalc(calCalc) {}

/*
   Initializes the TFT display, sets rotation,
   background color, and default text formatting.
*/
void Lcd::begin() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

/*
   Pulls step-related data from StepCounter and updates internal variables.
   This includes total step count, step rate (SPM), and current pace.
*/
void Lcd::setStepData() {
    stepCount = stepCounter.getStepCount();
    stepsPerMinute = stepCounter.getStepsPerMinute();
    pace = stepCounter.getPace();
}

/*
   Updates the latest heart rate (BPM) value from HeartRateMonitor.
*/
void Lcd::setHeartRate() {
    bpm = hrMonitor.getLatestBPM();
}

/*
   Fetches the total calories burned so far from CaloriesCalculator.
*/
void Lcd::setCalories() {
    calories = calCalc.getTotal();
}

/*
   Updates the status of the BLE connection from HeartRateMonitor.
   Used for showing BLE indicator in the UI.
*/
void Lcd::bluetoothStatus() {
    statusBLE = hrMonitor.isConnected();
}

/*
   Changes the screen to display either step tracking info or health stats.
   Prevents redundant redraws if the state hasn't changed.
*/
void Lcd::display(DisplayState newState) {
    if (newState == currentState) return;

    currentState = newState;

    switch (newState) {
        case DisplayState::StepsScreen:
            showStepsScreen();
            break;
        case DisplayState::StatsScreen:
            showStatsScreen();
            break;
    }
}

/*
   Renders the step tracking interface:
   - Shows total steps taken
   - Step goal progress (/10000)
   - Step rate (steps per minute)
*/
void Lcd::showStepsScreen() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);

    tft.setCursor(10, 10);
    tft.print("Steps");

    tft.setTextSize(4);
    tft.setCursor(10, 40);
    tft.printf("%05d", stepCount);  // Display with leading zeros (up to 5 digits)

    tft.setTextSize(2);
    tft.setCursor(10, 100);
    tft.print("/10000");  // Fixed goal display

    tft.setCursor(10, 130);
    tft.printf("Steps/min: %.1f", stepsPerMinute);  // SPM with 1 decimal
}

/*
   Renders the stats screen:
   - Displays heart rate in BPM
   - Displays calories burned
*/
void Lcd::showStatsScreen() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);

    tft.setCursor(10, 10);
    tft.print("HR: ");
    tft.setTextSize(4);
    tft.setCursor(60, 10);
    tft.printf("%d bpm", bpm);

    tft.setTextSize(2);
    tft.setCursor(10, 80);
    tft.print("Calories:");

    tft.setTextSize(3);
    tft.setCursor(10, 110);
    tft.printf("%d kcal", calories);
}

/*
   Draws shared UI elements that remain consistent across all screens:
   - Logo on the left
   - Bluetooth status indicator
   - Battery status (hardcoded for now)
   - Timer showing system uptime in MM:SS
*/
void Lcd::drawCommonUI() {
    tft.fillRect(0, 0, 240, 20, TFT_DARKGREY);  // Top bar background

    // Logo area
    tft.setCursor(5, 2);
    tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft.print("LOGO");

    // Bluetooth connection status
    tft.setCursor(80, 2);
    tft.print(statusBLE ? "BLE: OK" : "BLE: --");

    // Static battery level (replace with actual sensor later)
    tft.setCursor(160, 2);
    tft.print("BAT: 95%");

    // Elapsed time since power-on (uptime)
    tft.setCursor(200, 2);
    unsigned long seconds = millis() / 1000;
    tft.printf("%02lu:%02lu", seconds / 60, seconds % 60);
}
