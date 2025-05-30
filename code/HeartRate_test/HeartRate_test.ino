#include <Arduino.h>
#include "HeartRateMonitor.h"

HeartRateMonitor hrMonitor;

void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("Starting BLE Heart Rate Monitor...");
    hrMonitor.begin();
}

void loop() {
    hrMonitor.update();
    delay(10);
}
