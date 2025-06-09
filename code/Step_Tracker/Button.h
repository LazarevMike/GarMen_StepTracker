#ifndef BUTTON_H
#define BUTTON_H

class Button {
  public:
    Button(int btn_pin);
    bool getState();
    bool isPressed();
    bool isHeld();

  private:
    const int PIN_;
    bool last_state_;
    bool held_flag_;

    const int DEBOUNCE_ = 20;
    const int HOLD_INTERVAL = 500;

    unsigned int last_press_;

};

#endif