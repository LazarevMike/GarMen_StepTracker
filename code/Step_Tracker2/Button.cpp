#include "Arduino.h"
#include "Button.h"


Button::Button(int btn_pin) : PIN_(btn_pin) {
  pinMode(PIN_, INPUT);
  state_ = false;
  last_press_ = 0;
}

bool Button::getState() {
  return state_;
}

bool Button::isPressed() {
  bool new_state = digitalRead(PIN_);
  if(state_ != new_state && millis() - last_press_ > DEBOUNCE_) {
    state_ = new_state;
    last_press_ = millis();
    return state_;
  }
  return false;
}