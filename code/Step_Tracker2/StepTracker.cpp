#include <StepTracker.h>

StepTracker::StepTracker() {

}

void StepTracker::run() {
  
}

void StepTracker::start() {
  ui.begin();
  stepcounter.begin();
  heartmonitor.begin();

}