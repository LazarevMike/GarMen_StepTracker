#ifndef STEPTRACKER_H
#define STEPTRACKER_H

#include <Arduino.h>
#include <StepCounter.h>
#include <UserInterface.h>
#include <CaloriesCalculator.h>
#include <HeartRateMonitor.h>
#include <DisplayState.h>
#include <Clock.h>


class StepTracker {
public:

  StepTracker();

  void start();

  void update();

  void reset();

  void pause();

  void resume();

  void run();

  void calibrate();

  void selfTest();

  

private:
  // Modules of steptracker
  StepCounter stepcounter;
  UserInterface ui;
  HeartRateMonitor heartmonitor;
  Clock clock;
  
  // State controls
  bool isPaused;
  bool isCalibrating;
  DisplayState displaystate;
  Pace pace_;

  // Calibration controls
  unsigned long lastCalibPress;
  int selected_axis;


  void setLeds(Pace pace);
  float getMagnitude();
  
};

#endif