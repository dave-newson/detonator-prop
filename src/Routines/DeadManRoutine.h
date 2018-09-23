#ifndef DEADMAN_ROUTINE_H_
#define DEADMAN_ROUTINE_H_

#include "Hardware.h"
#include "Routine.h"
#include "Chrono.h"

#define ROUTINE_DEADMAN "deadman"

class DeadManRoutine : public Routine
{

public:
    DeadManRoutine(Hardware* _hardware);
    void before();
    void after();
    const char* getName() { return ROUTINE_DEADMAN; };
    void tick();

private:
    Hardware* hardware;
    bool trigger;

    void displayPrint(const char* message);
};

#endif