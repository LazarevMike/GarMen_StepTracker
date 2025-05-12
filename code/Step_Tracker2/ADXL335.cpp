#include "ADXL335.h"
#include "Arduino.h"

ADXL335::ADXL335(int x_pin, int y_pin, int z_pin, int st_pin) : X_PIN_(x_pin), Y_PIN_(y_pin), Z_PIN_(z_pin), ST_PIN_(st_pin) {
  pinMode(X_PIN_, INPUT);
  pinMode(Y_PIN_, INPUT);
  pinMode(Z_PIN_, INPUT);
  pinMode(ST_PIN_, OUTPUT);
  triggerSt(false);
}

int ADXL335::readX() {
  //The return value in inverted reading
  //Inversion is required as the output from hardaware is inverted.
  return 4095 - ADC_OFFSET_ * 2 - analogRead(X_PIN_);
}

int ADXL335::readY() {
  return analogRead(Y_PIN_);
}

int ADXL335::readZ() {
  return analogRead(Z_PIN_);
}

void ADXL335::triggerSt(bool new_state) {
  st_state_ = new_state;
  //Inverted because by design st pin driver is active low
  digitalWrite(ST_PIN_, !st_state_);
  
}

bool ADXL335::getStState() {
  return st_state_;
}

float ADXL335::convertADCtoAccel(int adc_reading) {
  float voltage = (adc_reading + ADC_OFFSET_)/4095.0 * 3.3;
  return (voltage - 1.65) / SENSITIVITY_;
}