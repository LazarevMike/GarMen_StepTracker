#include "soc/gpio_sig_map.h"
#include "UserInterface.h"
#include "Arduino.h"


UserInterface::UserInterface() :
  BLUE_LED_(35),
  ORANGE_LED_(36),
  GREEN_LED_(37),
  RESET_BTN_(21),
  START_BTN_(26),
  CALIB_BTN_(33)
{
  
}

void UserInterface::begin() {
  LCD_.begin();
}

void UserInterface::displaySteps() {
  LCD_.display(DisplayState::Steps);
}

void UserInterface::displayStats() {
  LCD_.display(DisplayState::Stats);

}

void UserInterface::displayCalib() {
  LCD_.display(DisplayState::Calibration);
}

void UserInterface::displayInfo(DisplayState state) {
  LCD_.display(state);
}

void UserInterface::reset() {
  updateStepData(0, 0, Pace::IDLE);
  updateHeartRate(0);
  updateCalories(0);
  updateBluetoothStatus(0);
  updateTime(0);
  // triggerBlue(0);
  // triggerGreen(0);
  // triggerOrange(0);
}

void UserInterface::updateStepData(int newSteps, int newspm, Pace newPace) {
  LCD_.setStepData(newSteps, newspm, newPace);
}

void UserInterface::updateHeartRate(int newBPM) {
  LCD_.setHeartRate(newBPM);
}

void UserInterface::updateCalories(int newCalories) {
  LCD_.setCalories(newCalories);
}

void UserInterface::updateBluetoothStatus(bool newStatusBLE) {
  LCD_.setBluetoothStatus(newStatusBLE);
}

void UserInterface::updateBatteryLevel(int newBatteryPercentage) {
  LCD_.setBatteryLevel(newBatteryPercentage);
}

void UserInterface::updateTime(unsigned long time) {
  LCD_.setTime(time);
}

void UserInterface::updateAxisAccels(int axis_id, float X_reading, float Y_reading, float Z_reading) {
  LCD_.setAxisAccels(axis_id, X_reading, Y_reading, Z_reading);
}

void UserInterface::testLeds() {
  std::vector<Led*> leds;
  leds.push_back(&BLUE_LED_);
  leds.push_back(&ORANGE_LED_);
  leds.push_back(&GREEN_LED_);

  for (int i = 0; i < 10; i++) {
    for (auto led : leds) {
      led->triggerLed(!led->getState());
      delay(500);
    }
  }
}

void UserInterface::testButtons() {
  unsigned int time = 0;
  while (time < 10000) {
    time = millis();
    triggerBlue(getResetState());
    triggerOrange(getStartState());
    triggerGreen(getCalibState());
    delay(50);
  }
}

bool UserInterface::isResetPressed() {
  return RESET_BTN_.isPressed();
}

bool UserInterface::isStartPressed() {
  return START_BTN_.isPressed();
}

bool UserInterface::isCalibPressed() {
  return CALIB_BTN_.isPressed();
}

std::vector<bool> UserInterface::buttonsStates() {
  std::vector<bool> states;
  states.push_back(getResetState());
  states.push_back(getStartState());
  states.push_back(getCalibState());
}

bool UserInterface::getResetState() {
  return RESET_BTN_.getState();
}

bool UserInterface::getStartState() {
  return START_BTN_.getState();
}

bool UserInterface::getCalibState() {
  return CALIB_BTN_.getState();
}

void UserInterface::triggerBlue(bool new_state) {
  BLUE_LED_.triggerLed(new_state);
}

void UserInterface::triggerOrange(bool new_state) {
  ORANGE_LED_.triggerLed(new_state);
}

void UserInterface::triggerGreen(bool new_state) {
  GREEN_LED_.triggerLed(new_state);
}
