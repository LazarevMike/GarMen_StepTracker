#include <Arduino.h>
#include "StepTracker.h"

// Required modules
StepTracker steptracker;

void setup() {
  steptracker.start();
}

void loop() {
  steptracker.run();
}