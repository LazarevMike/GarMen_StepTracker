const int buttonPins[3] = {2, 4, 5};  // GPIOs for your 3 buttons (active-low)
int currentButton = -1;               // which button’s handler we’re in

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  // 1) Sample all buttons
  int pressedCount = 0;
  int lastDetected = -1;
  for (int i = 0; i < 3; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      pressedCount++;
      lastDetected = i;
    }
  }

  // 2) Decide state
  if (pressedCount == 1) {
    // exactly one button held → start or switch to it
    if (lastDetected != currentButton) {
      currentButton = lastDetected;
      Serial.printf("Switched to handler %d\n", currentButton + 1);
    }
  }
  else if (pressedCount == 0) {
    // none pressed → go idle (so we can re-trigger next time)
    currentButton = -1;
  }
  // (pressedCount >= 2 → simultaneous: we just ignore)

  // 3) Run one “slice” of whichever handler is active
  //    Handlers must be non-blocking (i.e. quick steps)
  switch (currentButton) {
    case 0: onButton1Step(); break;
    case 1: onButton2Step(); break;
    case 2: onButton3Step(); break;
    default: /* idle */          break;
  }

  delay(10);  // small delay for debouncing & RTOS yield
}

// ——————————————————
// “Step”‐based handler stubs
// ——————————————————
// Break your long work into many small steps here so that
// if currentButton changes, the next loop() will switch immediately.

void onButton1Step() {
  Serial.println("Button 1 step");
  // … one quick piece of work …
}

void onButton2Step() {
  Serial.println("Button 2 step");
  // … one quick piece of work …
}

void onButton3Step() {
  Serial.println("Button 3 step");
  // … one quick piece of work …
}
