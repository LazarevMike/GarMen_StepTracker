#include "StepCalibrator.h"

/*
   Constructor initializes all counters and accumulators to default state.
*/
StepThresholdCalibrator::StepThresholdCalibrator()
    : idleMax(0), walkMax(0), runMax(0),
      idleSum(0), walkSum(0), runSum(0),
      idleCount(0), walkCount(0), runCount(0),
      currentState(NONE) {}

/*
   Begins the calibration process by resetting all counters and setting state to IDLE.
   Recommended sequence: IDLE → WALK → RUN (manually controlled by user).
*/
void StepThresholdCalibrator::beginCalibration() {
    idleMax = walkMax = runMax = 0;
    idleSum = walkSum = runSum = 0;
    idleCount = walkCount = runCount = 0;
    currentState = IDLE;
}

/*
   Updates statistics for the current state using the provided acceleration magnitude.
   Should be called continuously while the user is in the selected pace (IDLE/WALK/RUN).
*/
void StepThresholdCalibrator::update(float accelMagnitude) {
    updateStats(currentState, accelMagnitude);
}

/*
   Helper function that accumulates stats for a given movement state.
   Keeps track of max magnitude and running average.
*/
void StepThresholdCalibrator::updateStats(State state, float value) {
    switch (state) {
        case IDLE:
            idleSum += value;
            if (value > idleMax) idleMax = value;
            idleCount++;
            break;
        case WALK:
            walkSum += value;
            if (value > walkMax) walkMax = value;
            walkCount++;
            break;
        case RUN:
            runSum += value;
            if (value > runMax) runMax = value;
            runCount++;
            break;
        default:
            break;
    }
}

/*
   Marks the calibration process as complete by finalizing data.
   Can be used to switch out of calibration mode.
*/
void StepThresholdCalibrator::finish() {
    currentState = NONE;
}

/*
   Returns true when each pace state (IDLE, WALK, RUN) has sufficient samples collected.
   Threshold for completion can be adjusted if needed.
*/
bool StepThresholdCalibrator::isComplete() const {
    return idleCount >= 50 && walkCount >= 50 && runCount >= 50;
}

/*
   Computes idle threshold as average of max idle and min walk values.
   This helps distinguish between standing still and starting to walk.
*/
float StepThresholdCalibrator::getIdleThreshold() const {
    return (idleMax + walkMax) / 2.0f;
}

/*
   Computes walk threshold as average of max walk and min run values.
   This helps distinguish between walking and jogging/running.
*/
float StepThresholdCalibrator::getWalkThreshold() const {
    return (walkMax + runMax) / 2.0f;
}

/*
   Returns max acceleration observed while running.
   This value can optionally be used as an upper bound in step detection.
*/
float StepThresholdCalibrator::getRunThreshold() const {
    return runMax;
}
