#ifndef DEADMAN_ROUTINE_H_
#define DEADMAN_ROUTINE_H_

#include "Hardware/Hardware.h"
#include "Routine.h"
#include "Chrono.h"

#define ROUTINE_DEADMAN "deadman"

class DeadManRoutine : public Routine
{

    /**
     * Trigger states
     * DIRTY = Unknown; state needs to be cleaned
     * CLEAN = Verified unheld
     * HELD = Currently held down
     */
    enum TriggerState { DIRTY, CLEAN, HELD };

public:
    DeadManRoutine(Hardware* _hardware);
    void before();
    void after();
    const char* getName() { return ROUTINE_DEADMAN; };
    void tick();

private:
    Hardware* hardware;
    TriggerState trigger;
    Chrono timer1;
    Chrono timer2;
    Chrono timer3;

    void displayPrint(const char* message);
};

#endif