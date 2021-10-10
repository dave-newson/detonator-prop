#ifndef MANUAL_TRIGGER_ROUTINE_H_
#define MANUAL_TRIGGER_ROUTINE_H_

#include "Hardware/Hardware.h"
#include "Routine.h"
#include "Chrono.h"

#define ROUTINE_MANUAL_TRIGGER "manual_trigger"

class ManualTriggerRoutine : public Routine
{

    /**
     * State of the Trigger switch
     * DIRTY = Unknown, needs to be checked
     * CLEAN = Has been released, ready for use
     */
    enum TriggerState { DIRTY, CLEAN };

public:
    ManualTriggerRoutine(Hardware* _hardware);
    const char* getName() { return ROUTINE_MANUAL_TRIGGER; };
    void tick();
    void before();
    void after();

private:
    Hardware* hardware;
    TriggerState trigger;
    void displayPrint(const char* message, int offset);
};

#endif