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