#ifndef ADXL335_H
#define ADXL335_H

/*
  Custom made library for ADXL335 on GarMen PCB. 
  The pinout on PCB suggests pins for xyz as 8, 13, 9 correspondingly
  The st pin on PCB is pin 34.

  The library provider functions for reading from each axis and triggering st pin
*/

class ADXL335 {
  public:
    /*
    Constructor for the object.
    Sets class fields for pins, does pinModes and disables st pin.
    */ 
    ADXL335();      // Constructor
    
    //Reading ADC value from X axis
    int readX();

    //Reading ADC value from Y axis
    int readY();

    //Reading ADC value from Z axis
    int readZ();

    //Reading acceleration from X axis
    float readAccelX();

    //Reading acceleration from Y axis
    float readAccelY();
    
    //Reading acceleration from Z axis
    float readAccelZ();


    /*
    Triggering st pin to desired state defined by parameter new_state.
    1 or true enables self-test
    0 of false disables self-test
    */
    void triggerSt(bool new_state);

    /*
    Returns the current state of the st_pin
    1 or true: self-test enabled
    0 of false: self-test disabled
    */
    bool getStState();

    //Converts ADC reading into g reading using sensitivity of 330mV/g (from datasheet)
    float convertADCtoAccel(int adc_reading);

  private:
    //Pin numbers for xyz and st pin
    const int X_PIN_;
    const int Y_PIN_;
    const int Z_PIN_;
    const int ST_PIN_;

    //State variable of Self-test
    bool st_state_;
    
    /*
    Experimentally received value for ADC offset from 2048 (1.65V) at 0 g.
    Used for inverting signal from x axis and ADC to acceleration conversion.
    Explained by a slight voltage drop on the output resistor on each axis.
    */
    const int ADC_OFFSET_ = 138;

    //Sensitivity of ADXL335 from datasheet, experimentally defined to be at 0.31 (datasheet range 0.27 - 0.33)
    const float SENSITIVITY_ = 0.31;
};

#endif