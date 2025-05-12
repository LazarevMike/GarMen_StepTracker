#ifndef ADXL335_H
#define ADXL335_H


class ADXL335 {
  public:
    ADXL335(int x_pin, int y_pin, int z_pin, int st_pin);      // Constructor
    int readX();
    int readY();
    int readZ();
    void stOn();
    void stOff();
    bool getStState();

  private:
    int x_pin_;
    int y_pin_;
    int z_pin_;
    int st_pin_;
    bool st_state_;
};

#endif