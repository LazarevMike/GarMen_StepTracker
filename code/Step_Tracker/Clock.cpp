#include "Clock.h"

void Clock::start() {
    reset();
}

void Clock::reset() {
    startTimeStamp = millis();
    pauseTimeAccum = 0;
    isPaused = false;
}

void Clock::pause() {
    if (!isPaused) {
        pauseTimeAccum += millis() - startTimeStamp;
        isPaused = true;
    }
}

void Clock::resume() {
    if (isPaused) {
        startTimeStamp = millis();
        isPaused = false;
    }
}

unsigned long Clock::getElapsedTime() {
    if (isPaused) {
        return pauseTimeAccum / 1000;
    } else {
        return (pauseTimeAccum + (millis() - startTimeStamp)) / 1000;
    }
}