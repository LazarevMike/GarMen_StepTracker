#include <Arduino.h>
#include "StepTracker.h"

// Required modules
StepTracker steptracker;

void setup() {
  //Serial.begin(115200);
  steptracker.start();
}

void loop() {
  steptracker.run();
}