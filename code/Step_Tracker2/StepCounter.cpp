#include "StepCounter.h"

/*
   Constructor initializes internal state and clears timestamp buffer.
*/
StepCounter::StepCounter()
    : stepCount(0),
      lastStepTime(0),
      lastResetTime(0),
      stepTimestampIndex(0),
      currentPace(IDLE),
      X_offset(0),
      Y_offset(0),
      Z_offset(0)
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
void StepCounter::update() {
    float mag = calculateMagnitude(adxl.readAccelX(), adxl.readAccelY(), adxl.readAccelZ());
    unsigned long now = millis();
    unsigned long stepInterval = now - lastStepTime;

    if (detectStep(mag) && stepInterval >= MIN_STEP_INTERVAL) {
        stepCount++;
        
        lastStepTime = now;

        // Store timestamp for step-per-minute estimation
        stepTimestamps[stepTimestampIndex] = now;
        stepTimestampIndex = (stepTimestampIndex + 1) % 20;

        // Update pace (Idle, Walk, Run) based on timing between steps
        updatePace(stepInterval);
    }

    if (stepInterval > IDLE_THRESHOLD) {
        updatePace(stepInterval);
    }
}

void StepCounter::adjustX() {
    X_offset = 1.0 - getX();
}

void StepCounter::adjustY() {
    Y_offset = 1.0 - getY();
}

void StepCounter::adjustZ() {
    Z_offset = - 1.0 - getZ();
}

/*
   Calculates the magnitude of the 3D acceleration vector.
*/
float StepCounter::calculateMagnitude(float x, float y, float z) {
    return sqrt(x * x + y * y + z * z);
}

float StepCounter::getMagnitude() {
    return calculateMagnitude(getX(), getY(), getZ());
}

/*
   Detects steps based on threshold-based peak/trough detection.
   Uses simple high/low band logic to debounce step events.
*/
bool StepCounter::detectStep(float magnitude) {
    static float prevMag = 0;
    static bool stepInProgress = false;

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
    if (stepInterval > IDLE_THRESHOLD) {
        currentPace = IDLE;
    } else if (stepInterval > WALKING_THRESHOLD) {
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
int StepCounter::getStepsPerMinute() const {
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

float StepCounter::getX() {
    return adxl.readAccelX() + X_offset;
}
    
float StepCounter::getY() {
    return adxl.readAccelY() + Y_offset;
}

float StepCounter::getZ() {
    return adxl.readAccelZ() + Z_offset;
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
