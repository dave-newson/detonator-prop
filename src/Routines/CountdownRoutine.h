#ifndef COUNTDOWN_ROUTINE_H_
#define COUNTDOWN_ROUTINE_H_

#include "Hardware/Hardware.h"
#include "Routine.h"
#include "Chrono.h"

#define ROUTINE_COUNTDOWN "countdown"

class CountdownRoutine : public Routine
{

public:
    CountdownRoutine(Hardware* hardware);
    void before();
    void after();
    const char* getName() { return ROUTINE_COUNTDOWN; };
    void tick();
    void start(Routine* _returnAfter);

private:
    Hardware* hardware;
    Chrono timer1;
    unsigned int duration;
};

#endif