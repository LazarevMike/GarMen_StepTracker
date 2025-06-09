#ifndef LED_H
#define LED_H

/*
  Simple library to use LED. Allows triggering led into desired state and keeps the current state as boolean.
*/

class Led {
  public:
    //Object constructor. Takes LED's pin as parametes, sets the pin as output and turns LED off.
    Led(int led_pin);
    
    /*
    Change the state of the LED into a desired state. 
    1 or true: LED on
    0 of false: LED off
    */
    void triggerLed(bool new_state);

    /*
    Returns current state of the LED
    1 or true: LED on
    0 of false: LED off
    */
    bool getState();

  private:
    //Assigned pin for the led
    const int PIN_;

    //Current state
    bool state_;

};

#endif