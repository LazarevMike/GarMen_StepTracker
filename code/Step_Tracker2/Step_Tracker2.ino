#include "ADXL335.h"
#include "UserInterface.h"


ADXL335 adxl(8, 13, 9, 34);
UserInterface ui(35, 36, 37, 21, 26, 33);
unsigned int last_trigger = 0;

void setup() {
  Serial.begin(115200);

}

void loop() {
  ui.testLeds();


  // //Serial.print("Current X: ");
  // Serial.print(-3.6);       // lower bound
  // Serial.print("\t");
  // Serial.print(3.6);    // upper bound
  // Serial.print("\t");
  // //Serial.print(adxl.readX());
  // Serial.print(adxl.convertADCtoAccel(adxl.readX()));
  // Serial.print("\t");
  // //Serial.print(adxl.readY());
  // Serial.print(adxl.convertADCtoAccel(adxl.readY()));
  // Serial.print("\t");
  // //Serial.println(adxl.readZ());
  // Serial.println(adxl.convertADCtoAccel(adxl.readZ()));

  // delay(50);

  // // if (millis() - last_trigger > 1000) {
  // //   adxl.triggerSt(!adxl.getStState());
  // //   last_trigger = millis();
  // // }

}
