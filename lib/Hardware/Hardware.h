#ifndef HARDWARE_H
#define HARDWARE_H

#include "Keypad.h"
#include "RGBLed.h"
#include "Adafruit_SSD1306.h"
#include "Switch.h"
#include "Led.h"
#include "beeper.h"

class Hardware {

public:
    Keypad* keypad;
    RGBLed* led1;
    RGBLed* led2;
    RGBLed* led3;
    Adafruit_SSD1306* display;
    Led* ledDebug;
    Led* ledArmed;
    Switch* armed;
    Switch* trigger;
    Beeper* beeper;

    void reset();

};

#endif