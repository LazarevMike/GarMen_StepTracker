#include "ADXL335.h"

ADXL335 adxl(8, 13, 9, 34);

unsigned int last_trigger = 0;

void setup() {
  Serial.begin(115200);

}

void loop() {
  //Serial.print("Current X: ");
  Serial.print(-3.6);       // lower bound
  Serial.print("\t");
  Serial.print(3.6);    // upper bound
  Serial.print("\t");
  //Serial.print(adxl.readX());
  Serial.print(adxl.convertADCtoAccel(adxl.readX()));
  Serial.print("\t");
  //Serial.print(adxl.readY());
  Serial.print(adxl.convertADCtoAccel(adxl.readY()));
  Serial.print("\t");
  //Serial.println(adxl.readZ());
  Serial.println(adxl.convertADCtoAccel(adxl.readZ()));

  // int x = adxl.readX();
  // int y = adxl.readY();
  // if (x == y) {
  //   Serial.print("\t");
  //   Serial.println(x);
  // }
  delay(50);

  // if (millis() - last_trigger > 1000) {
  //   adxl.triggerSt(!adxl.getStState());
  //   last_trigger = millis();
  // }

}
