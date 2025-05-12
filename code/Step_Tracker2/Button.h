#ifndef BUTTON_H
#define BUTTON_H

class Button {
  public:
    Button(int btn_pin);
    bool getState();

  private:
    const int PIN_;
    bool state_;

};

#endif