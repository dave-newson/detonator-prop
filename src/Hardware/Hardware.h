#ifndef HARDWARE_H
#define HARDWARE_H

#include "RGBLed.h"
#include "Switch.h"
#include "Led.h"
#include "beeper.h"
#include "Module/DisplayModule.h"
#include "Module/KeypadModule.h"

class Hardware {

public:

    // Low level hardware
    RGBLed* led1;
    RGBLed* led2;
    RGBLed* led3;
    Led* ledDebug;
    Led* ledArmed;
    Switch* armed;
    Switch* trigger;
    Beeper* beeper;

    // Drivers
    DisplayModule* display;
    KeypadModule* keypad;

    void tick();
    void reset();

};

#endif