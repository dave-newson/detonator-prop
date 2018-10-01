#include "KeypadModule.h"
#include "Log.h"

#define KEY_BEEP_DURATION 100
#define KEY_BEEP_MIN_HZ 100
#define KEY_BEEP_MAX_HZ 200

KeypadModule::KeypadModule(Keypad* keypad, Beeper* beeper)
{
    _keypad = keypad;
    _beeper = beeper;
}

char KeypadModule::getKey()
{
    char key = _keypad->getKey();

    if (key) {
        onKeyPress(key);
    }

    return key;
}

void KeypadModule::tick()
{
    if (timer1.hasPassed(KEY_BEEP_DURATION)) {
        _beeper->silence();
        timer1.stop();
        timer1.restart();
    }
}

void KeypadModule::onKeyPress(char key)
{
    timer1.start();
    timer1.restart();
    int tone = 0;

    switch (key) {
        case '*':
            tone = KEY_BEEP_MIN_HZ - 200;
            break;
        case '#':
            tone = KEY_BEEP_MIN_HZ - 100;
            break;
        default:
            tone = KEY_BEEP_MIN_HZ + (key * ((KEY_BEEP_MAX_HZ - KEY_BEEP_MIN_HZ) / 9));
    }

    _beeper->note(tone);
}