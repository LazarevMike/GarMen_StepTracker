#include "StepCounter.h"

/*
   Constructor initializes internal state and clears timestamp buffer.
*/
StepCounter::StepCounter()
    : stepCount(0),
      lastStepTime(0),
      lastResetTime(0),
      stepTimestampIndex(0),
      currentPace(IDLE)
{
    memset(stepTimestamps, 0, sizeof(stepTimestamps));
}

/*
   Called once at startup to initialize reset time.
*/
void StepCounter::begin() {
    lastResetTime = millis();
}

/*
   Main update method that should be called periodically.
   Computes acceleration magnitude, detects steps, timestamps them,
   and updates pace classification.
*/
void StepCounter::update(float accelX, float accelY, float accelZ) {
    float mag = calculateMagnitude(accelX, accelY, accelZ);

    if (detectStep(mag)) {
        stepCount++;
        unsigned long now = millis();

        unsigned long interval = now - lastStepTime;
        lastStepTime = now;

        // Store timestamp for step-per-minute estimation
        stepTimestamps[stepTimestampIndex] = now;
        stepTimestampIndex = (stepTimestampIndex + 1) % 20;

        // Update pace (Idle, Walk, Run) based on timing between steps
        updatePace(interval);
    }
}

/*
   Calculates the magnitude of the 3D acceleration vector.
*/
float StepCounter::calculateMagnitude(float x, float y, float z) {
    return sqrt(x * x + y * y + z * z);
}

/*
   Detects steps based on threshold-based peak/trough detection.
   Uses simple high/low band logic to debounce step events.
*/
bool StepCounter::detectStep(float magnitude) {
    static float prevMag = 0;
    static bool stepInProgress = false;

    float thresholdHigh = 1.2f; // Step detected when passing above this
    float thresholdLow = 0.8f;  // Confirmed step when dropping below this

    bool isStep = false;

    if (!stepInProgress && magnitude > thresholdHigh) {
        stepInProgress = true;
    } else if (stepInProgress && magnitude < thresholdLow) {
        isStep = true;
        stepInProgress = false;
    }

    prevMag = magnitude;
    return isStep;
}

/*
   Determines current pace classification based on time between steps.
   Uses simple thresholds for distinguishing walk/run/idle.
*/
void StepCounter::updatePace(unsigned long stepInterval) {
    if (stepInterval > 2000) {
        currentPace = IDLE;
    } else if (stepInterval > 500) {
        currentPace = WALK;
    } else {
        currentPace = RUN;
    }
}

/*
   Returns the total number of detected steps since last reset.
*/
int StepCounter::getStepCount() const {
    return stepCount;
}

/*
   Returns the number of steps taken in the last 60 seconds.
   Used to estimate steps per minute (SPM).
*/
int StepCounter::getStepsPerMinute() {
    unsigned long now = millis();
    int validSteps = 0;

    for (int i = 0; i < 20; i++) {
        if (stepTimestamps[i] != 0 && now - stepTimestamps[i] <= 60000) {
            validSteps++;
        }
    }

    return validSteps;
}

/*
   Returns the current pace classification (Idle, Walk, Run).
*/
Pace StepCounter::getPace() const {
    return currentPace;
}

/*
   Resets step counter, pace, and all internal state for fresh measurement.
*/
void StepCounter::reset() {
    stepCount = 0;
    stepTimestampIndex = 0;
    lastStepTime = 0;
    lastResetTime = millis();
    currentPace = IDLE;
    memset(stepTimestamps, 0, sizeof(stepTimestamps));
}
