#include <StepTracker.h>

StepTracker::StepTracker() {
  start();
}

void StepTracker::run() {
  stepcounter.update();
  ui.updateStepData(stepcounter.getStepCount(), stepcounter.getStepsPerMinute(), stepcounter.getPace());
  ui.displaySteps();
  delay(20);

}

void StepTracker::start() {
  ui.begin();
  stepcounter.begin();
  heartmonitor.begin();
}