#include "Arduino.h"
#include "Beeper.h"

Beeper::Beeper(int beeperPin)
{
    pin = beeperPin;
    pinMode(pin, OUTPUT);
}

void Beeper::note(uint16_t freq)
{
    tone(pin, freq);
}

void Beeper::note(uint16_t freq, uint32_t duration)
{
    tone(pin, freq, duration);
}

void Beeper::silence()
{
    noTone(pin);
}