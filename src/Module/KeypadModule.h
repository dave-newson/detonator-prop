#ifndef KEYPAD_MODULE_H_
#define KEYPAD_MODULE_H_

#include "Keypad.h"
#include "Beeper.h"
#include "Chrono.h"

class KeypadModule
{

public:
    KeypadModule(Keypad* keypad, Beeper* beeper);
    void tick();
    char getKey();
    
private:
    Keypad* _keypad;
    Beeper* _beeper;
    Chrono timer1;

    void onKeyPress(char key);

};

#endif