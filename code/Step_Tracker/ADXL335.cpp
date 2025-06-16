#include "ADXL335.h"
#include "Arduino.h"

ADXL335::ADXL335() : X_PIN_(8), Y_PIN_(13), Z_PIN_(9), ST_PIN_(34), 
X_ADC_OFFSET_(DEFALUT_ADC_OFFSET_), Y_ADC_OFFSET_(DEFALUT_ADC_OFFSET_), Z_ADC_OFFSET_(DEFALUT_ADC_OFFSET_) {
  pinMode(X_PIN_, INPUT);
  pinMode(Y_PIN_, INPUT);
  pinMode(Z_PIN_, INPUT);
  pinMode(ST_PIN_, OUTPUT);
  triggerSt(false);
}

int ADXL335::readX() {
  return analogRead(X_PIN_);
}

int ADXL335::readY() {
  return analogRead(Y_PIN_);
}

int ADXL335::readZ() {
  return analogRead(Z_PIN_);
}

void ADXL335::adjustOffsetX() {
  X_ADC_OFFSET_ = ((1.65 - SENSITIVITY_) / 3.3) * 4095 - readX();
}

void ADXL335::adjustOffsetY() {
  Y_ADC_OFFSET_ = ((1.65 + SENSITIVITY_) / 3.3) * 4095 - readY();
}
    
void ADXL335::adjustOffsetZ() {
  //Because adjusting on -g
  Z_ADC_OFFSET_ = ((1.65 - SENSITIVITY_) / 3.3) * 4095 - readZ();
}

float ADXL335::readAccelX() {
  // By hardware x is inverted
  return -convertADCtoAccel(readX() + X_ADC_OFFSET_);
}

float ADXL335::readAccelY() {
  return convertADCtoAccel(readY() + Y_ADC_OFFSET_);
}
    

float ADXL335::readAccelZ() {
  return convertADCtoAccel(readZ() + Z_ADC_OFFSET_);
}

void ADXL335::triggerSt(bool new_state) {
  st_state_ = new_state;
  //Inverted because by design st pin driver is active low
  digitalWrite(ST_PIN_, !st_state_);
}

bool ADXL335::selfTest() {
  float x1 = readAccelX();
  float y1 = readAccelY();
  float z1 = readAccelZ();
  triggerSt(true);
  delay(300);
  float x2 = readAccelX();
  float y2 = readAccelY();
  float z2 = readAccelZ();
  bool outcome = (x2 - x1 > -0.9 && y2 - y1 > 0.9 && z2 - z1 > 1.5);
  triggerSt(false);
  return outcome; 
}

bool ADXL335::getStState() {
  return st_state_;
}

float ADXL335::convertADCtoAccel(int adc_reading) {
  float voltage = (adc_reading)/4095.0 * 3.3;
  return (voltage - 1.65) / SENSITIVITY_;
}