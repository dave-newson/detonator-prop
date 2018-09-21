#include "Arduino.h"
#include "Switch.h"

Switch::Switch(int switchPin)
{
    pin = switchPin;
    pinMode(pin, INPUT_PULLUP);
};

bool Switch::isOn()
{
    return !digitalRead(pin);
};