#include "ADXL335.h"

ADXL335 adxl(8, 13, 9, 34);

unsigned int last_trigger = 0;

void setup() {
  Serial.begin(115200);
  //adxl.stOn();

}

void loop() {
  //Serial.print("Current X: ");
  Serial.print(0);       // lower bound
  Serial.print("\t");
  Serial.print(4096);    // upper bound
  Serial.print("\t");
  Serial.print(adxl.readX());
  Serial.print("\t");
  Serial.print(adxl.readY());
  Serial.print("\t");
  Serial.println(adxl.readZ());
  delay(50);

  // if (millis() - last_trigger > 1000) {
  //   if (adxl.getStState()) {
  //     adxl.stOff();
  //   }
  //   else {
  //     adxl.stOn();
  //   }
  //   last_trigger = millis();

  // }

}
