#include "DisplayState.h"
#include <Arduino.h>
#include <StepTracker.h>

StepTracker::StepTracker() : displaystate(DisplayState::Steps), pace_(Pace::IDLE), isPaused(false) {

}

void StepTracker::run() {
  if (!isPaused) {
    update();
  }

  if (isCalibrating) {
    calibrate();
  }
  else {

  if (ui.isCalibPressed()) {
    if (millis() - lastCalibPress < 500) {
      displaystate = DisplayState::Calibration;
      selected_axis = 0;
      pause();
      isCalibrating = true;
    }
    else {
    lastCalibPress = millis();

    switch (displaystate) {
      case DisplayState::Steps:
        displaystate = DisplayState::Stats;
        break;

      case DisplayState::Stats:
        displaystate = DisplayState::Steps;
        break;
      
      case DisplayState::Calibration:
        displaystate = DisplayState::Steps;
        break;
    }
    }
  }

  if (ui.isStartPressed()) {
    if (isPaused) {
      resume();
    }
    else {
      pause();
    }
  }

  if (ui.isResetHeld()) {
    reset();
  }
  }

  ui.displayInfo(displaystate);
}

void StepTracker::start() {
  ui.begin();
  stepcounter.begin();
  heartmonitor.begin();
  clock.start();
  selfTest();
  setLeds(pace_);
}

void StepTracker::reset() {
  ui.reset();
  stepcounter.reset();
  CaloriesCalculator::resetTotal();
  heartmonitor.update();
  clock.reset();
}

void StepTracker::pause() {
  isPaused = true;
  clock.pause();
  ui.triggerBlue(1);
  ui.triggerGreen(1);
  ui.triggerOrange(1);
  ui.updatePause(isPaused); 
}

void StepTracker::resume() {
  isPaused = false;
  clock.resume();
  setLeds(pace_);
  ui.updatePause(isPaused);
  update();
}

void StepTracker::update() {
  stepcounter.update();
  heartmonitor.update();
  ui.updateBluetoothStatus(heartmonitor.isConnected());
  ui.updateHeartRate(heartmonitor.getLatestBPM());
  Pace new_pace = stepcounter.getPace();
  ui.updateStepData(stepcounter.getStepCount(), stepcounter.getStepsPerMinute(), new_pace);
  CaloriesCalculator::update(heartmonitor, stepcounter);

  ui.updateCalories(CaloriesCalculator::getTotal());
  ui.updateTime(clock.getElapsedTime());

  if (new_pace != pace_) {
    pace_ = new_pace;
    setLeds(pace_);
  }
}

void StepTracker::setLeds(Pace pace) {
  switch (pace) {
    case Pace::IDLE:
      ui.triggerBlue(0);
      ui.triggerOrange(0);
      ui.triggerGreen(1);
      break;
      
    case Pace::WALK:
      ui.triggerBlue(0);
      ui.triggerOrange(1);        
      ui.triggerGreen(0);
      break;

    case Pace::RUN:
      ui.triggerBlue(1);
      ui.triggerOrange(0);
      ui.triggerGreen(0);
      break;
  }
}

float StepTracker::getMagnitude() {
  return stepcounter.getMagnitude();
}

void StepTracker::calibrate() {
  ui.updateAxisAccels(selected_axis, stepcounter.getX(), stepcounter.getY(), stepcounter.getZ());
  if (ui.isCalibPressed()) {
    switch (selected_axis) {
      case 0:
        stepcounter.adjustX();
        break;
      case 1:
        stepcounter.adjustY();
        break;
      case 2:
        stepcounter.adjustZ();
        break;
    }
    selected_axis++;
    if (selected_axis == 3) {
      selected_axis = 0;
      isCalibrating = false;
      displaystate = DisplayState::Steps;
      resume();
    }
  }
}

void StepTracker::selfTest() {
  displaystate = DisplayState::SelfTest;
  ui.displayInfo(displaystate);
  bool outcome = stepcounter.selfTest();
  if (outcome) {
    ui.triggerBlue(true);
  }
  else {
    ui.triggerOrange(true);
  }

  ui.updateSTOutcome(outcome);
  ui.displayInfo(displaystate);
  delay(1000);
  displaystate = DisplayState::Steps;
}