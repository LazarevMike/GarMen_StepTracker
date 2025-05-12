#include "ADXL335.h"
#include "UserInterface.h"


ADXL335 adxl(8, 13, 9, 34);
UserInterface ui(35, 36, 37, 21, 26, 33);
unsigned int last_trigger = 0;
int counter1 = 0;
int counter2 = 0;
int counter3 = 0;

void setup() {
  Serial.begin(115200);

}

void loop() {
  //ui.testLeds();
  Serial.print(ui.getResetState());
  Serial.print("\t");
  Serial.print(ui.getStartState());
  Serial.print("\t");
  Serial.println(ui.getCalibState());
  // for (bool sta : ui.buttonsStates()) {
  //   Serial.println(sta);
  // }
  // if (ui.isResetPressed()) {
  //   counter1++;
  //   Serial.print("RESET button was pressed ");
  //   Serial.println(counter1);
  // }
  // if (ui.isStartPressed()) {
  //   counter2++;
  //   Serial.print("START button was pressed ");
  //   Serial.println(counter2);
  // }
  // if (ui.isCalibPressed()) {
  //   counter3++;
  //   Serial.print("CALIBRATION button was pressed ");
  //   Serial.println(counter3);
  // }

  delay(200);
  


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
