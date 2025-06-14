#include "Adafruit_ST77xx.h"
#include "Lcd.h"  // Include header for Lcd class

// Define display control pins
#define TFT_CS   5
#define TFT_RST  6
#define TFT_DC   7

// Initialize the TFT display object
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

// Constructor to link external data sources (step counter, HR monitor, calorie tracker)
Lcd::Lcd()
    :
      canvas(280, 240), 
      currentState(DisplayState::Steps),
      stepCount(0),
      stepsPerMinute(0),
      bpm(0),
      calories(0),
      statusBLE(false),
      pace(Pace::IDLE),
      lastSwitchTime(0),
      lastBatteryTime(0),
      isRunning(true),
      isPaused(false),
      STOutcome(false),
      STReceived(false) {}

// Initialize the TFT display
void Lcd::begin() {
    tft.init(240, 280);         // Set screen dimensions
    tft.setRotation(3);         // Landscape orientation
    tft.fillScreen(ST77XX_BLACK);
    canvas.setTextColor(ST77XX_WHITE);
    canvas.setTextWrap(false);
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
void Lcd::setBluetoothStatus(bool newStatusBLE) {
    statusBLE = newStatusBLE;
}

//Update battery level
void Lcd::setBatteryLevel(int newBatteryPercentage) {
    batteryPercentage = newBatteryPercentage;
}

void Lcd::setTime(unsigned long time) {
    seconds = time;
}   

void Lcd::setPaused(bool paused) {
    isPaused = paused;
}   

void Lcd::setAxisAccels(int axis_id, float X_reading, float Y_reading, float Z_reading) {
    selected_axis = axis_id;
    X_axis = X_reading;
    Y_axis = Y_reading;
    Z_axis = Z_reading;
}

void Lcd::setSTOutcome(bool outcome) {
    STReceived = true;
    STOutcome = outcome;
}

// Change screen based on state (steps/stats)
void Lcd::display(DisplayState newState) {

    unsigned long now = millis();
    unsigned long interval = 1000 / REFRESH_HZ;

    if (now - lastRefreshTime < interval) {
        return;  // Not time to refresh yet
    }

    lastRefreshTime = now;

    currentState = newState;

    canvas.fillScreen(ST77XX_BLACK);  // full redraw

    switch (currentState) {
        case DisplayState::Steps:
            showStepsScreen();
            break;
        case DisplayState::Stats:
            showStatsScreen();
            break;
        case DisplayState::Calibration:
            showCalibrationScreen();
            break; 
        case DisplayState::SelfTest:
            showSelfTestScreen();
            break;
    }

    tft.drawRGBBitmap(0, 0, canvas.getBuffer(), 280, 240);
}

// Draw step tracking screen with SPM, step count, and icon
void Lcd::showStepsScreen() {
    drawCommonUI();          // Optional top bar with time/BLE

    updateStateImage();      // Animate walk/idle icon

    canvas.setTextSize(4);
    canvas.setCursor(80, 130);
    canvas.printf("%05d", stepCount);

    canvas.setTextSize(2.5);
    canvas.setCursor(100, 170);
    canvas.print("/10000");

    canvas.setTextSize(2);
    canvas.setCursor(85, 200);
    canvas.printf("SPM %.1f", stepsPerMinute);

    canvas.drawRGBBitmap(170, 197, flame_small_img, 19, 19);
}

// Draw stats screen with heart rate and calories
void Lcd::showStatsScreen() {
    drawCommonUI();          // Optional top bar with time/BLE

    canvas.drawRGBBitmap(25, 82, heart_img, 49, 49);
    canvas.setTextSize(5);
    canvas.setCursor(80, 90);
    canvas.printf("HR:%d", bpm);

    canvas.drawRGBBitmap(25, 142, flame_big_img, 30, 36);
    canvas.setTextSize(4);
    canvas.setCursor(70, 150);
    canvas.printf("kCal:%d", calories);
}

// Draw top bar with app name, BLE status, battery, and runtime clock
void Lcd::drawCommonUI() {
    canvas.setTextSize(2);
    canvas.setTextColor(ST77XX_WHITE);
    canvas.setCursor(105, 20);
    canvas.print("GarMen");  // App title

    bluetoothStateImage();  // Draw BLE icon

    canvas.drawRGBBitmap(220, 10, battery_img, 52, 52);
    batteryLevel();  // Draw battery fill bars

    // Runtime timer
    canvas.setTextSize(2);
    canvas.setCursor(10, 20);
    canvas.printf("%02lu:%02lu", seconds / 60, seconds % 60);

    if (isPaused) {
        canvas.drawRGBBitmap(220, 190, pause_img, 44, 44);
    }
}

// Draw BLE connection icon depending on connection state
void Lcd::bluetoothStateImage() {
    if (statusBLE == true) {
        canvas.drawRGBBitmap(15, 200, bluetooth_img, 32, 32);
    } else {
        canvas.drawRGBBitmap(15, 200, noBluetooth_img, 32, 32);
    }
}

// Switches between walk and idle icons every 5s
void Lcd::updateStateImage() {
    int xImg = (280 - 80) / 2;
    int yImg = 40;

    const uint16_t* img = nullptr;
    int h = 0;

    switch (pace) {
        case Pace::IDLE:
            img = idle_img;
            h = 88;
            break;

        case Pace::WALK:
            img = walk_img;
            h = 82;
            break;

        case Pace::RUN:
            img = run_img;
            h = 82;
            break;
        
        default:
            img = idle_img;
            h = 88;
            break;
    }
    
    // Display state image
    canvas.drawRGBBitmap(xImg, yImg, img, 80, h);
}

// Simulates battery indicator with 3 blocks
void Lcd::batteryLevel() {
    batteryPercentage = 100;
    if (batteryPercentage < 33) {
        // Low: only 1 bar
        canvas.fillRect(223, 26, 12, 20, ST77XX_WHITE);
        canvas.fillRect(237, 26, 12, 20, ST77XX_BLACK);
        canvas.fillRect(251, 26, 12, 20, ST77XX_BLACK);
    } else if (batteryPercentage >= 33 && batteryPercentage < 66) {
        // Medium: 2 bars
        canvas.fillRect(223, 26, 12, 20, ST77XX_WHITE);
        canvas.fillRect(237, 26, 12, 20, ST77XX_WHITE);
        canvas.fillRect(251, 26, 12, 20, ST77XX_BLACK);
    } else if (batteryPercentage >= 66 && batteryPercentage <= 100) {
        // Full: all 3 bars
        canvas.fillRect(223, 26, 12, 20, ST77XX_WHITE);
        canvas.fillRect(237, 26, 12, 20, ST77XX_WHITE);
        canvas.fillRect(251, 26, 12, 20, ST77XX_WHITE);
    }
}

// Draw calibration screen with axis values axis calibrating
void Lcd::showCalibrationScreen() {
    drawCommonUI();

    canvas.setTextSize(3);
    canvas.setCursor(20, 80);
    canvas.printf("Calib axis:%s", axisLabels[selected_axis]);

    canvas.setTextSize(2);
    canvas.setCursor(20, 140);
    canvas.printf("X:%.2f", X_axis);

    canvas.setCursor(100, 170);
    canvas.printf("Y:%.2f", Y_axis);

    canvas.setCursor(180, 140);
    canvas.printf("Z:%.2f", Z_axis);
}

void Lcd::showSelfTestScreen() {
    drawCommonUI();
    canvas.setTextSize(2);
    canvas.setCursor(10, 80);
    canvas.print("Self-test in progress.");

    if (STReceived) {
        canvas.setTextSize(5);
        canvas.setCursor(50, 140);
        if (STOutcome) {
            canvas.setTextColor(ST77XX_GREEN);
            canvas.print("PASSED");
        }
        else {
            canvas.setTextColor(ST77XX_RED);
            canvas.print("FAILED");
        }
    }
}
