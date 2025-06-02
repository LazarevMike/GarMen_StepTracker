#ifndef STEPCALIBRATOR_H
#define STEPCALIBRATOR_H

/*
   Class responsible for collecting and analyzing accelerometer magnitude data
   during different movement states (IDLE, WALK, RUN) to determine threshold
   values for step detection and pace classification.
*/
class StepCalibrator {
public:
    // Constructor initializes all internal counters and states
    StepCalibrator();

    // Starts the calibration process by resetting all stats and setting the initial state
    void beginCalibration();

    // Feeds new accelerometer magnitude value into the current calibration state
    void update(float accelMagnitude);

    // Returns true if enough samples have been collected for all movement states
    bool isComplete() const;

    // Finalizes calibration and computes averaged thresholds based on collected data
    void finish();

    // Returns calculated threshold between idle and walk
    float getIdleThreshold() const;

    // Returns calculated threshold between walk and run
    float getWalkThreshold() const;

    // Returns maximum observed magnitude during running
    float getRunThreshold() const;

private:
    // Maximum observed magnitude per movement state
    float idleMax, walkMax, runMax;

    // Accumulated sum of magnitudes per movement state
    float idleSum, walkSum, runSum;

    // Number of samples collected per movement state
    int idleCount, walkCount, runCount;

    // Defines the movement state currently being calibrated
    enum State { NONE, IDLE, WALK, RUN };
    State currentState;

    // Helper to update internal statistics for the specified state
    void updateStats(State state, float value);
};

#endif // STEPCALIBRATOR_H