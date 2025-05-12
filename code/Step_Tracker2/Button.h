#ifndef BUTTON_H
#define BUTTON_H

class Button {
  public:
    Button(int btn_pin);
    bool getState();
    bool isPressed();

  private:
    const int PIN_;
    bool state_;

    const int DEBOUNCE_ = 20;
    unsigned int last_press_;

};

#endif