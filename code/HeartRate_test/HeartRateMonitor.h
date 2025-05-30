#ifndef HEARTRATEMONITOR_H
#define HEARTRATEMONITOR_H

#include <Arduino.h>
#include <NimBLEDevice.h>

/*
   Class responsible for connecting to a BLE heart rate monitor (e.g. Polar H10),
   subscribing to notifications, and exposing the latest BPM reading.
*/
class HeartRateMonitor {
public:
    // Constructor: Initializes internal state
    HeartRateMonitor();

    // Initializes BLE stack and begins scanning for devices
    void begin();

    // Main update loop, to be called from Arduino's loop()
    void update();

private:
    // Pointer to the BLE device that advertises the Heart Rate Service
    NimBLEAdvertisedDevice* advDevice;

    // Client used for connecting and subscribing to BLE characteristics
    NimBLEClient* client;

    // Stores the most recent BPM reading from BLE notifications
    volatile uint16_t latestBPM;

    // Flag indicating that a new BPM value is available for processing
    volatile bool newBPMAvailable;

    // Indicates whether a device is currently connected
    bool connected;

    // Flag to trigger a connection attempt after a device is found
    bool doConnect;

    // Static pointer to allow access from the static BLE callback
    static HeartRateMonitor* instancePtr;

    // Scans available BLE devices for one advertising the Heart Rate Service
    void handleScanResults();

    // Attempts to connect to the discovered BLE device and subscribe to heart rate notifications
    bool connect();

    // Static callback function to handle heart rate notifications
    static void heartRateNotifyCB(NimBLERemoteCharacteristic* pChar, uint8_t* data, size_t length, bool isNotify);
};

#endif // HEARTRATEMONITOR_H
