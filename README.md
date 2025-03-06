# Step_Tracker_EMS_2025
Code for step tracker for Embeded Mechatronics System Autumn 2025 UTS. Using Arduino Nano ESP32 and custom made PCB in Altium Designer.

# StepTracker_ADXL335_Arduino

![Step Tracker System](assets/step_tracker_banner.png)

## Project Overview
This repository contains the Arduino code for the **Step Tracker System** using the ADXL335 accelerometer and a custom PCB shield for the Arduino UNO R3. The project aims to count steps, identify walking pace, and provide a reliable user interface using LEDs and an LCD display.

## Features
- **Step Counting:** Accurate step detection for any orientation of the accelerometer.
- **Walking Pace Identification:** Identifies stationary, walking, and running paces with indicator LEDs.
- **Self-Test Protocol:** Verifies accelerometer functionality using the ST pin of ADXL335.
- **Static Acceleration Calibration:** Calibrates the sensor against static gravitational force for all six directions (+/-X, +/-Y, +/-Z).
- **Dual Power Options:** Supports external power via a DC barrel connector and a battery for mobile operation.
- **Signal Conditioning:** Includes analog filters for X, Y, and Z-axis signals.
- **User Interface:** 
  - LCD display for step count and pace information.
  - LEDs for power and pace indication.
  - Button for calibration and resetting step count.
- **BNC Connector Output:** Provides a filtered Z-axis signal for testing with lab equipment.

---

## Bill of Materials (BOM)
- **Arduino Nano ESP32**
- **ADXL335 Accelerometer (Breakout PCB)**
- **Custom PCB Shield**
- **1.69" LCD**
- **LEDs:** Power indicator, pace indicators
- **Buttons:** User input for calibration and reset
- **Power Supplies:** External DC and battery
- **Connectors:**
  - Amphenol ICC Minitek127 for ADXL335 interface
  - BNC connector for Z-axis output

---

## Folder Structure
