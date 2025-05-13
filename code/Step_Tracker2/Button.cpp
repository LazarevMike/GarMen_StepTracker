#include "Arduino.h"
#include "Button.h"


Button::Button(int btn_pin) : PIN_(btn_pin) {
  pinMode(PIN_, INPUT);
  last_state_ = false;
  last_press_ = 0;
}

bool Button::getState() {
  return digitalRead(PIN_);
}

bool Button::isPressed() {
  bool new_state = getState();
  if(last_state_ != new_state && millis() - last_press_ > DEBOUNCE_) {
    last_state_ = new_state;
    last_press_ = millis();
    return last_state_;
  }
  return false;
}