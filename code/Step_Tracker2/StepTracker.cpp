#include <Arduino.h>
#include <StepTracker.h>

StepTracker::StepTracker() {

}

void StepTracker::run() {
  stepcounter.update();
  ui.updateStepData(stepcounter.getStepCount(), stepcounter.getStepsPerMinute(), stepcounter.getPace());
  ui.displaySteps();
  //delay(1000);

}

void StepTracker::start() {
  ui.begin();
  stepcounter.begin();
  heartmonitor.begin();
}