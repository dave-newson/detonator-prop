#include "Led.h"
#include "Arduino.h"

Led::Led(int ledPin)
{
    pin = ledPin;
    pinMode(pin, OUTPUT);
}

void Led::on()
{
    state = true;
    digitalWrite(pin, HIGH);
}

void Led::off()
{
    state = false;
    digitalWrite(pin, LOW);
}


bool Led::isOn()
{
    return state;
}