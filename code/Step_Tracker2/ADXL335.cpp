#include "ADXL335.h"
#include "Arduino.h"

ADXL335::ADXL335() : X_PIN_(8), Y_PIN_(13), Z_PIN_(9), ST_PIN_(34) {
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


float ADXL335::readAccelX() {
  return convertADCtoAccel(readX());
}


float ADXL335::readAccelY() {
  return convertADCtoAccel(readY());
}
    

float ADXL335::readAccelZ() {
  return convertADCtoAccel(readZ());
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