#include <Arduino.h>
#include "HeartRateMonitor.h"
#include "CaloriesCalculator.h"
#include "StepCounter.h"
#include "Lcd.h"
#include "StepTracker.h"
#include "UserInterface.h"

// Required modules
// HeartRateMonitor hrMonitor;
// StepCounter dummyStepCounter;  // Placeholder for now
// CaloriesCalculator calCalc;
//Lcd lcd;
// StepCounter stepcounter;


StepTracker steptracker;
//UserInterface ui;

void setup() {
  Serial.begin(115200);

  steptracker.start();
  
}

void loop() {
  steptracker.run();
  Serial.println(steptracker.getMagnitude());

}