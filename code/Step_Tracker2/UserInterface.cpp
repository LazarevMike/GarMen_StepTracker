#include "UserInterface.h"
#include "Arduino.h"


UserInterface::UserInterface(int blueLed_pin, int orangeLed_pin, int greenLed_pin, int resetBtn_pin, int startBtn_pin, int calibBtn_pin) :
  BLUE_LED_(blueLed_pin),
  ORANGE_LED_(orangeLed_pin),
  GREEN_LED_(greenLed_pin),
  RESET_BTN_(resetBtn_pin),
  START_BTN_(startBtn_pin),
  CALIB_BTN_(calibBtn_pin)
{
  
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
