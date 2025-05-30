#include "Lcd.h"
#include "Arduino.h"
#include "StepCounter.h"  // For accessing step, pace, and SPM data

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <math.h> // For sqrt calculations (if needed in future)

#include "media/whiterun_rgb565_fixed.h"
#include "media/idle_white_on_black_80x88.h"
#include "media/flame_icon.h"

// Global TFT screen instance
TFT_eSPI tft = TFT_eSPI(); // Change if using a different screen library

/*
   Constructor initializes internal UI state and all sensor display values to zero.
*/
Lcd::Lcd()
    : currentState(DisplayState::StepsScreen),
      stepCount(0),
      stepsPerMinute(0),
      bpm(0),
      calories(0),
      statusBLE(false) {}

/*
   Initializes the screen. Sets rotation, clears the display, and configures default text colors.
*/
void Lcd::begin() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
}

/*
   Fetches the current step data from StepCounter.
   Updates internal step count, steps per minute, and detected pace.
*/
void Lcd::setStepData() {
    stepCount = StepCounter::getStepCount();
    stepsPerMinute = StepCounter::getStepsPerMinute();
    pace = StepCounter::getPace();
}

/*
   Retrieves the current heart rate value from the HeartRateMonitor.
*/
void Lcd::setHeartRate() {
    bpm = HeartRateMonitor::getLatestBPM();
}

/*
   Retrieves the total calories burned from CaloriesCalculator.
*/
void Lcd::setCalories() {
    calories = CaloriesCalculator::getTotal();
}

/*
   Updates BLE connection status by querying HeartRateMonitor.
*/
void Lcd::bluetoothStatus() {
    statusBLE = HeartRateMonitor::isConnected();
}

/*
   Main function to switch between display modes (step screen or stats screen).
   Avoids unnecessary redraws if the same screen is already active.
*/
void Lcd::display(DisplayState newState) {
    if (newState == currentState) return; // Prevent redundant redraws

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
   Renders the step tracking screen:
   Displays total steps, goal progress, and steps per minute.
*/
void Lcd::showStepsScreen() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);

    tft.setCursor(10, 10);
    tft.print("Steps");

    tft.setTextSize(4);
    tft.setCursor(10, 40);
    tft.printf("%05d", stepCount);  // Leading zeros, 5 digits

    tft.setTextSize(2);
    tft.setCursor(10, 100);
    tft.print("/10000");

    tft.setCursor(10, 130);
    tft.printf("Steps/min: %.1f", stepsPerMinute);

    // Optional: Add pace icon, BLE icon, etc.
}


/*
   Renders the stats screen:
   Shows heart rate and calories burned so far.
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

    // Optional: Add fire icon for intensity or achievements
}


void Lcd::drawCommonUI() {
    // Top bar background
    tft.fillRect(0, 0, 240, 20, TFT_DARKGREY);

    // Logo
    tft.setCursor(5, 2);
    tft.setTextColor(TFT_WHITE, TFT_DARKGREY);
    tft.print("LOGO");

    // Bluetooth status
    tft.setCursor(80, 2);
    if (statusBLE) {
        tft.print("BLE: OK");
    } else {
        tft.print("BLE: --");
    }

    // Battery level (placeholder)
    tft.setCursor(160, 2);
    tft.print("BAT: 95%");

    // Timer (e.g., uptime or session duration)
    tft.setCursor(200, 2);
    unsigned long seconds = millis() / 1000;
    tft.printf("%02lu:%02lu", seconds / 60, seconds % 60);
}
