#include <Arduino.h>
#include "HeartRateMonitor.h"
#include "CaloriesCalculator.h"
#include "StepCounter.h"
#include "Lcd.h"

// Required modules
HeartRateMonitor hrMonitor;
StepCounter dummyStepCounter;  // Placeholder for now
CaloriesCalculator calCalc;
Lcd lcd;
StepCounter stepcounter;

// Timer for screen switching
unsigned long lastSwitchTime = 0;
bool showStats = false;

void setup() {
  Serial.begin(115200);
  hrMonitor.begin();
  lcd.begin();  // Initialize display
  stepcounter.begin();
}

void loop() {


  stepcounter.update();
  Serial.println(stepcounter.getStepCount());
  // hrMonitor.update();                   // Check BLE for BPM updates
  // CaloriesCalculator::update(hrMonitor);  // ✅ Pass the object explicitly

   unsigned long now = millis();
   if (now - lastSwitchTime >= 10000) {
     lastSwitchTime = now;
     showStats = !showStats;  // Toggle screen state
   }

   if (showStats) {
     lcd.display(DisplayState::StatsScreen);  // HR & Calories
   } else {
     lcd.display(DisplayState::StepsScreen);  // Steps & Pace
   }

  //Serial.println(calCalc.getTotal());

  delay(100);          // Smooth refresh rate
}