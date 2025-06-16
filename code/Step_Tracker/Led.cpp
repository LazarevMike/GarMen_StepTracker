#include "Arduino.h"
#include "Led.h"


Led::Led(int led_pin) : PIN_(led_pin) {
  pinMode(PIN_, OUTPUT);
  triggerLed(false);
}

void Led::triggerLed(bool new_state) {
  state_ = new_state;
  digitalWrite(PIN_, state_);  
}

bool Led::getState() {
  return state_;
}