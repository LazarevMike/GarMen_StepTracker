#include <Arduino.h>
#include <StepTracker.h>

StepTracker::StepTracker() : displaystate(DisplayState::Steps) {

}

void StepTracker::run() {
  stepcounter.update();
  heartmonitor.update();
  CaloriesCalculator::update(heartmonitor, stepcounter);

  switch (displaystate) {
    case DisplayState::Steps:
      ui.updateStepData(stepcounter.getStepCount(), stepcounter.getStepsPerMinute(), stepcounter.getPace());
      break;

    case DisplayState::Stats:
      ui.updateHeartRate(heartmonitor.getLatestBPM());
      ui.updateCalories(CaloriesCalculator::getTotal());
      break;
    
    case DisplayState::Calibration:
      break;
  
  }

  if (ui.isCalibPressed()) {
    switch (displaystate) {
      case DisplayState::Steps:
        displaystate = DisplayState::Stats;
        break;

      case DisplayState::Stats:
        displaystate = DisplayState::Steps;
        break;
    }
  
  }

  ui.displayInfo(displaystate);
  //delay(1000);
}

void StepTracker::start() {
  ui.begin();
  stepcounter.begin();
  heartmonitor.begin();
}