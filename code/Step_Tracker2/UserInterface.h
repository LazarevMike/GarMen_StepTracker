#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include "Led.h"
#include "Button.h"

/*
  Class for User Interface.
  Keeps all the UI elements, including LEDs, Buttons and LCD display as fields.
  Has methods to test LEDs, nothing else yet.
*/

class UserInterface {
  public:
    /*
    Constructor of the class.
    Sets initialises Led and Button objects and assignes pins to them. Turns all the LEDs off.
    */
    UserInterface(int blueLed_pin, int orangeLed_pin, int greenLed_pin, int resetBtn_pin, int startBtn_pin, int calibBtn_pin);

    /*
    Method to test functionality of all the leds in the UI. 
    Blinks all the leds 5 times in a sequence  using delay (not asynchronous function)
    */
    void testLeds();

  private:
    // All the Led objects in the UI
    Led BLUE_LED_;
    Led ORANGE_LED_;
    Led GREEN_LED_;

    // All the Button objects in the UI
    Button RESET_BTN_;
    Button START_BTN_;
    Button CALIB_BTN_;

};

#endif