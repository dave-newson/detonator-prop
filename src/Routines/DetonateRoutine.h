#ifndef DETONATE_ROUTINE_H_
#define DETONATE_ROUTINE_H_

#include "Hardware.h"
#include "Routine.h"
#include "Chrono.h"

#define ROUTINE_DETONATE "detonate"

class DetonateRoutine : public Routine
{

public:
    DetonateRoutine(Hardware* hardware);
    void before();
    void after();
    const char* getName() { return ROUTINE_DETONATE; };
    void tick();
    void start(Routine* _returnAfter);

private:
    Hardware* hardware;
    Chrono timer1;
    Routine* returnRoutine = nullptr;
    int stage = 0;
};

#endif