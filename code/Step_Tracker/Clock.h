#ifndef CLOCK_H
#define CLOCK_H

#include <Arduino.h>

class Clock {
public:
    void start();
    void pause();
    void resume();
    void reset();
    unsigned long getElapsedTime(); // in seconds

private:
    unsigned long startTimeStamp = 0;
    unsigned long pauseTimeAccum = 0;
    bool isPaused = false;
};

#endif