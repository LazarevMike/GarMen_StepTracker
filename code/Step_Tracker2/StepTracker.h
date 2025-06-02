#ifndef STEPTRACKER_H
#define STEPTRACKER_H

#include <Arduino.h>
#include <StepCounter.h>
#include <UserInterface.h>
#include <CaloriesCalculator.h>
#include <HeartRateMonitor.h>


class StepTracker {
public:

  StepTracker();

  void start();

  void update();

  void reset();

  void pause();

  void resume();

private:
  StepCounter stepcounter;
  UserInterface ui;


};

#endif