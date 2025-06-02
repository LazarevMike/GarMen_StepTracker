#ifndef STEPCOUNTER_H
#define STEPCOUNTER_H

#include <Arduino.h>
#include <ADXL335.h>

/*
   Enum to classify pace based on step frequency.
   Used for determining activity state: idle, walking, or running.
*/
enum Pace {
    IDLE,
    WALK,
    RUN
};

/*
   Class responsible for detecting steps based on accelerometer input,
   estimating steps per minute (SPM), and determining pace (idle, walk, run).
*/
class StepCounter {
public:
    // Constructor initializes internal state
    StepCounter();

    // Initializes timestamp tracking and resets counters
    void begin();

    // Main update function, should be called at a consistent rate (e.g. 50–100 Hz)
    void update();

    // Returns total step count since last reset
    int getStepCount() const;

    // Returns estimated steps per minute (based on last 60 seconds)
    int getStepsPerMinute() const;;

    // Returns current detected pace (Idle, Walk, or Run)
    Pace getPace() const;

    // Resets all internal counters and timestamps
    void reset();

private:
    // Step tracking
    int stepCount;
    unsigned long lastStepTime;
    unsigned long lastResetTime;
    const unsigned long MIN_STEP_INTERVAL = 250;

    float thresholdHigh = 1.2f; // Step detected when passing above this
    float thresholdLow = 0.8f;  // Confirmed step when dropping below this

    ADXL335 adxl;

    // Rolling buffer to store timestamps of recent steps (for SPM calc)
    int stepTimestamps[20];
    int stepTimestampIndex;

    // Current pace classification
    Pace currentPace;

    // Calculates magnitude of 3D acceleration vector
    float calculateMagnitude(float x, float y, float z);

    // Returns true if current magnitude indicates a step
    bool detectStep(float magnitude);

    // Updates the pace state based on the time between recent steps
    void updatePace(unsigned long stepInterval);
};

#endif // STEPCOUNTER_H
