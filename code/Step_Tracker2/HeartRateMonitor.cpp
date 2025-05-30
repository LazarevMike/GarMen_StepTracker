#include "HeartRateMonitor.h"

#define HEART_RATE_SERVICE_UUID        "180D"
#define HEART_RATE_MEASUREMENT_UUID   "2A37"

// Static pointer used to reference the class instance inside the static callback
HeartRateMonitor* HeartRateMonitor::instancePtr = nullptr;

/*
   Constructor initializes all internal state variables.
*/
HeartRateMonitor::HeartRateMonitor()
    : advDevice(nullptr),
      client(nullptr),
      latestBPM(0),
      newBPMAvailable(false),
      connected(false),
      doConnect(false) {}

/*
   Static notification callback for BLE heart rate data.
   Extracts BPM value from received data and stores it for printing in the main loop.
*/
void HeartRateMonitor::heartRateNotifyCB(NimBLERemoteCharacteristic* pChar, uint8_t* data, size_t length, bool isNotify) {
    if (length >= 2 && instancePtr != nullptr) {
        uint8_t flags = data[0];
        uint16_t bpm = (flags & 0x01) == 0
            ? data[1]                            // 8-bit BPM
            : (data[1] | (data[2] << 8));        // 16-bit BPM

        instancePtr->latestBPM = bpm;
        instancePtr->newBPMAvailable = true;
    }
}

/*
   Iterates over scan results to find a device advertising the Heart Rate Service.
   Stores reference to the matching device and stops scanning.
*/
void HeartRateMonitor::handleScanResults() {
    NimBLEScanResults results = NimBLEDevice::getScan()->getResults();

    for (int i = 0; i < results.getCount(); i++) {
        const NimBLEAdvertisedDevice* device = results.getDevice(i);

        if (device->isAdvertisingService(NimBLEUUID(HEART_RATE_SERVICE_UUID))) {
            Serial.println("Found device with Heart Rate Service.");
            advDevice = const_cast<NimBLEAdvertisedDevice*>(device);
            doConnect = true;
            NimBLEDevice::getScan()->stop();
            break;
        }
    }
}

/*
   Establishes BLE connection to the discovered device and subscribes to the
   heart rate characteristic for notifications.

   Returns true on successful connection and subscription, false otherwise.
*/
bool HeartRateMonitor::connect() {
    client = NimBLEDevice::createClient();

    if (!client->connect(advDevice)) {
        Serial.println("Failed to connect.");
        NimBLEDevice::deleteClient(client);
        return false;
    }

    Serial.println("Connected to device.");

    NimBLERemoteService* service = client->getService(HEART_RATE_SERVICE_UUID);
    if (!service) {
        Serial.println("Heart Rate Service not found.");
        client->disconnect();
        return false;
    }

    NimBLERemoteCharacteristic* characteristic = service->getCharacteristic(HEART_RATE_MEASUREMENT_UUID);
    if (!characteristic || !characteristic->canNotify()) {
        Serial.println("Heart Rate Characteristic not found or notifications not supported.");
        client->disconnect();
        return false;
    }

    if (!characteristic->subscribe(true, heartRateNotifyCB)) {
        Serial.println("Subscription to notifications failed.");
        client->disconnect();
        return false;
    }

    Serial.println("Subscribed to heart rate notifications.");
    connected = true;
    return true;
}

/*
   Initializes BLE stack, sets scan parameters, and starts scanning for BLE heart rate monitors.
   Also stores instance pointer to enable use of static callback.
*/
void HeartRateMonitor::begin() {
    instancePtr = this;

    NimBLEDevice::init("ESP32-HRM");

    NimBLEScan* scan = NimBLEDevice::getScan();
    scan->setActiveScan(true);     // Request additional advertising data
    scan->setInterval(45);         // How frequently to scan (in 0.625 ms units)
    scan->setWindow(15);           // How long to scan during each interval
    scan->start(0);                // 0 = scan indefinitely
}

/*
   This function should be called repeatedly in the main loop.
   It manages device discovery, connection attempts, and safely prints BPM when new data is available.
*/
void HeartRateMonitor::update() {
    // Continue processing scan results if not yet connected
    if (!connected) {
        handleScanResults();
    }

    // Attempt connection if a valid device was found
    if (doConnect && !connected) {
        doConnect = false;
        if (!connect()) {
            Serial.println("Connection failed. Restarting scan...");
            NimBLEDevice::getScan()->start(0);
        }
    }

    // Print latest heart rate reading, ensuring safe access to shared data
    if (newBPMAvailable) {
        noInterrupts();
        uint16_t bpmToPrint = latestBPM;
        newBPMAvailable = false;
        interrupts();

        Serial.printf("Heart Rate (BPM): %d\n", bpmToPrint);
    }
}
