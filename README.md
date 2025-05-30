# Step_Tracker_EMS_2025

Code for step tracker for Embedded Mechatronic Systems (Autumn 2025) at UTS.  
Using Arduino Nano ESP32 and a custom-designed PCB in Altium Designer.

![Step Tracker System](assets/step_tracker_banner.png)

---

## 📌 Project Overview

This repository contains the Arduino code for the **Step Tracker System** using the ADXL335 accelerometer and a custom PCB shield for the Arduino UNO R3.  
The system counts steps, identifies walking pace, monitors heart rate and calories, and provides a clean user interface using an LCD screen.

---

## 🚀 Features

- **Step Counting**: Accurate detection using analog acceleration.
- **Pace Detection**: Classifies movement as Idle, Walk, or Run.
- **Heart Rate Monitoring**: Connects to BLE HR sensors (e.g., Polar H10).
- **Calories Burned Calculation**: Uses Zillman formula for accurate kcal estimation.
- **User Interface**:
  - LCD screen with different display modes (Steps / Stats).
  - Bluetooth connectivity status, battery level (optional), and timer.
- **Self-Test Protocol**: Validates ADXL335 using the ST pin.
- **Static Acceleration Calibration**: Calibrates ±X, ±Y, ±Z axes using known gravity values.
- **Dual Power Input**: Runs from DC barrel jack or battery.
- **Signal Conditioning**: Filters analog signals before ADC sampling.
- **BNC Output**: Clean analog Z-axis output for lab validation.

---

## 📦 Required Libraries

Before compiling and uploading, make sure the following Arduino libraries are installed:

| Library | Purpose |
|--------|---------|
| [`Adafruit GFX Library`](https://github.com/adafruit/Adafruit-GFX-Library) | Core graphics support for LCD display |
| [`Adafruit ST7735 and ST7789 Library`](https://github.com/adafruit/Adafruit-ST7735-Library) | Driver for 1.69" TFT LCD |
| [`TFT_eSPI`](https://github.com/Bodmer/TFT_eSPI) | High-performance display driver |
| [`NimBLE-Arduino`](https://github.com/h2zero/NimBLE-Arduino) | Efficient BLE (Bluetooth Low Energy) support for ESP32 |

> 🛠️ **Install these using**:  
> `Arduino IDE → Sketch → Include Library → Manage Libraries`  
> Or manually from GitHub into your `libraries` folder.

---

## 📁 Folder Structure

```text
/Step_Tracker/
│
├── StepTrackerProject.ino         # Main Arduino sketch (setup and loop)
├── SensorManager.cpp/.h           # Manages accelerometer readings and filtering
├── StepCounter.cpp/.h             # Step detection and pace classification logic
├── CaloriesCalculator.cpp/.h      # Calorie computation based on HR and weight
├── HeartRateMonitor.cpp/.h        # BLE client for heart rate monitor devices
├── DisplayManager.cpp/.h          # UI and screen switching (Steps/Stats)
├── Lcd.cpp/.h                     # LCD screen control using Adafruit or TFT_eSPI
├── StepThresholdCalibrator.cpp/.h# Threshold learning system for walking/running
└── Config.h                       # Configuration constants
