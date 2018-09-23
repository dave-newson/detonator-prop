#ifndef HARDWARE_TEST_ROUTINE_H_
#define HARDWARE_TEST_ROUTINE_H_

#include "Hardware.h"
#include "Routine.h"
#include "Chrono.h"

#define ROUTINE_HARDWARE_TEST "hardware_test"

class HardwareTestRoutine : public Routine
{

public:
    HardwareTestRoutine(Hardware* _hardware);
    const char* getName() { return ROUTINE_HARDWARE_TEST; };
    void tick();
    void before();
    void after() {};

private:
    Hardware* hardware;
    Chrono timer1;
    Chrono timer2;
    Chrono timer3;
    int colorSlide;

    void resetDisplay();

};

#endif