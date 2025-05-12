#include "ADXL335.h"
#include "Arduino.h"

ADXL335::ADXL335(int x_pin, int y_pin, int z_pin, int st_pin) : x_pin_(x_pin), y_pin_(y_pin), z_pin_(z_pin), st_pin_(st_pin) {
  pinMode(x_pin_, INPUT);
  pinMode(y_pin_, INPUT);
  pinMode(z_pin_, INPUT);
  pinMode(st_pin_, OUTPUT);
  stOff();
}

int ADXL335::readX() {
  return analogRead(x_pin_);
}

int ADXL335::readY() {
  return analogRead(y_pin_);
}

int ADXL335::readZ() {
  return analogRead(y_pin_);
}

void ADXL335::stOn() {
  digitalWrite(st_pin_, LOW);
  st_state_ = true;
}

void ADXL335::stOff() {
  digitalWrite(st_pin_, HIGH);
  st_state_ = false;
}

bool ADXL335::getStState() {
  return st_state_;
}