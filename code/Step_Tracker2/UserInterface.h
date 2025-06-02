#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "Led.h"
#include "Button.h"
#include "Lcd.h"
#include <DisplayState.h>
#include <vector>

/*
  Class for User Interface.
  Keeps all the UI elements, including LEDs, Buttons and LCD display as fields.
  Has methods to test LEDs, nothing else yet.

  The pins for components dictated by hardware are as following:
    Blue LED: 35
    Orange LED: 36
    Green LED: 37
    Reset button: 21 (left button)
    Start/Pause button: 26 (middle button)
    Calibration button: 33 (right button)
*/

class UserInterface {
  public:
    /*
    Constructor of the class.
    Sets initialises Led and Button objects and assignes pins to them. Turns all the LEDs off.
    */
    UserInterface();

    void begin();

    void displaySteps();

    void displayStats();

    void displayCalib();

    void displayInfo(DisplayState state);

    // Gathers and updates current step data from StepCounter
    void updateStepData(int newSteps, int newspm, Pace newPace);

    // Retrieves the latest BPM from HeartRateMonitor
    void updateHeartRate(int newBPM);

    // Retrieves total burned calories from CaloriesCalculator
    void updateCalories(int newCalories);

    // Updates the BLE connection status
    void updateBluetoothStatus(bool newStatusBLE);

    //Update battery level
    void updateBatteryLevel(int newBatteryPercentage);

    /*
    Method to test functionality of all the leds in the UI. 
    Blinks all the leds 5 times in a sequence  using delay (not asynchronous function)
    */
    void testLeds();

    void testButtons();

    bool isResetPressed();
    bool isStartPressed();
    bool isCalibPressed();
    std::vector<bool> buttonsStates();

    bool getResetState();
    bool getStartState();
    bool getCalibState();

    void triggerBlue(bool new_state);
    void triggerOrange(bool new_state);
    void triggerGreen(bool new_state);

  private:
    // All the Led objects in the UI
    Led BLUE_LED_;
    Led ORANGE_LED_;
    Led GREEN_LED_;

    // All the Button objects in the UI
    Button RESET_BTN_;
    Button START_BTN_;
    Button CALIB_BTN_;

    Lcd LCD_;

};

#endif