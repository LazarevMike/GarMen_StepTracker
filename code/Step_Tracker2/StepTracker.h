#ifndef STEPTRACKER_H
#define STEPTRACKER_H

#include <Arduino.h>
#include <StepCounter.h>
#include <UserInterface.h>
#include <CaloriesCalculator.h>
#include <HeartRateMonitor.h>
#include <DisplayState.h>


class StepTracker {
public:

  StepTracker();

  void start();

  void update();

  void reset();

  void pause();

  void resume();

  void run();

private:
  StepCounter stepcounter;
  UserInterface ui;
  HeartRateMonitor heartmonitor;
  DisplayState displaystate;
  
};

#endif