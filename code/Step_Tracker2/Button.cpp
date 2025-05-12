#include "Arduino.h"
#include "Button.h"


Button::Button(int btn_pin) : PIN_(btn_pin) {
  pinMode(PIN_, INPUT);
  state_ = false;
}

bool Button::getState() {
  return state_;
}