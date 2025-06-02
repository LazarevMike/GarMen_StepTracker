#include "Lcd.h"  // Include header for Lcd class

// Define display control pins
#define TFT_CS   5
#define TFT_RST  6
#define TFT_DC   7

// Initialize the TFT display object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Constructor to link external data sources (step counter, HR monitor, calorie tracker)
Lcd::Lcd()
    : currentState(DisplayState::StepsScreen),
      stepCount(0),
      stepsPerMinute(0),
      bpm(0),
      calories(0),
      statusBLE(false),
      pace(Pace::IDLE),
      lastSwitchTime(0),
      lastBatteryTime(0),
      isRunning(true) {}

// Initialize the TFT display
void Lcd::begin() {
    tft.init(240, 280);         // Set screen dimensions
    tft.setRotation(3);         // Landscape orientation
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextWrap(false);
}

// Update step-related data from StepCounter
void Lcd::setStepData(int newSteps, int newspm, Pace newPace) {
    stepCount = newSteps;
    stepsPerMinute = newspm;
    pace = newPace;
}

// Update current heart rate from HR monitor
void Lcd::setHeartRate(int newBPM) {
    bpm = newBPM;
}

// Update total calories burned
void Lcd::setCalories(int newCalories) {
    calories = newCalories;
}

// Update BLE connection status
void Lcd::bluetoothStatus(bool newStatusBLE) {
    statusBLE = newStatusBLE;
}

//Update battery level
void Lcd::setBatteryLevel(int newBatteryPercentage) {
    batteryPercentage = newBatteryPercentage;
}

// Change screen based on state (steps/stats)
void Lcd::display(DisplayState newState) {
    if (newState == currentState) return;  // Prevent unnecessary redraw

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

// Draw step tracking screen with SPM, step count, and icon
void Lcd::showStepsScreen() {
    tft.fillScreen(ST77XX_BLACK);
    drawCommonUI();          // Optional top bar with time/BLE

    updateStateImage();      // Animate walk/idle icon

    tft.setTextSize(4);
    tft.setCursor(80, 130);
    tft.printf("%05d", stepCount);

    tft.setTextSize(2.5);
    tft.setCursor(100, 170);
    tft.print("/10000");

    tft.setTextSize(2);
    tft.setCursor(85, 200);
    tft.printf("SPM %.1f", stepsPerMinute);

    tft.drawRGBBitmap(170, 197, flame_small_img, 19, 19);  // Flame icon next to SPM
}

// Draw stats screen with heart rate and calories
void Lcd::showStatsScreen() {
    tft.fillScreen(ST77XX_BLACK);
    drawCommonUI();          // Optional top bar with time/BLE

    tft.drawRGBBitmap(25, 82, heart_img, 49, 49);
    tft.setTextSize(5);
    tft.setCursor(80, 90);
    tft.printf("HR:%d", bpm);

    tft.drawRGBBitmap(25, 142, flame_big_img, 30, 36);
    tft.setTextSize(4);
    tft.setCursor(70, 150);
    tft.printf("kCal:%d", calories);
}

// Draw top bar with app name, BLE status, battery, and runtime clock
void Lcd::drawCommonUI() {

    tft.setTextSize(2);
    tft.setCursor(105, 20);
    tft.print("GarMen");  // App title

    bluetoothStateImage();  // Draw BLE icon

    tft.drawRGBBitmap(220, 10, battery_img, 52, 52);
    batteryLevel();  // Draw battery fill bars

    // Runtime timer
    tft.setTextSize(2);
    tft.setCursor(10, 20);
    unsigned long seconds = millis() / 1000;
    tft.printf("%02lu:%02lu", seconds / 60, seconds % 60);
}

// Draw BLE connection icon depending on connection state
void Lcd::bluetoothStateImage() {
    if (statusBLE == true) {
        tft.drawRGBBitmap(15, 200, bluetooth_img, 32, 32);
    } else {
        tft.drawRGBBitmap(15, 200, noBluetooth_img, 32, 32);
    }
}

// Switches between walk and idle icons every 5s
void Lcd::updateStateImage() {
    if (millis() - lastSwitchTime >= 5000) {
        lastSwitchTime = millis();
        isRunning = !isRunning;

        int xImg = (280 - 80) / 2;
        int yImg = 40;
        tft.fillRect(xImg, yImg, 80, 90, ST77XX_BLACK);  // Clear previous image
        const uint16_t* img = isRunning ? walk_img : idle_img;
        int h = isRunning ? 82 : 88;
        tft.drawRGBBitmap(xImg, yImg, img, 80, h);
    }
}

// Simulates battery indicator with 3 blocks
void Lcd::batteryLevel() {

    if (batteryPercentage < 33) {
        // Low: only 1 bar
        tft.fillRect(223, 26, 12, 20, ST77XX_WHITE);
        tft.fillRect(237, 26, 12, 20, ST77XX_BLACK);
        tft.fillRect(251, 26, 12, 20, ST77XX_BLACK);
    } else if (batteryPercentage >= 33 && batteryPercentage < 66) {
        // Medium: 2 bars
        tft.fillRect(223, 26, 12, 20, ST77XX_WHITE);
        tft.fillRect(237, 26, 12, 20, ST77XX_WHITE);
        tft.fillRect(251, 26, 12, 20, ST77XX_BLACK);
    } else if (batteryPercentage >= 66 && batteryPercentage <= 100) {
        // Full: all 3 bars
        tft.fillRect(223, 26, 12, 20, ST77XX_WHITE);
        tft.fillRect(237, 26, 12, 20, ST77XX_WHITE);
        tft.fillRect(251, 26, 12, 20, ST77XX_WHITE);
    }
}
