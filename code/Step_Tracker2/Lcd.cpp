#include "Lcd.h"
#include "Arduino.h"

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include <math.h> // for sqrt

#include "media/whiterun_rgb565_fixed.h"
#include "media/idle_white_on_black_80x88.h"
#include "media/flame_icon.h"

Lcd::Lcd() {

}