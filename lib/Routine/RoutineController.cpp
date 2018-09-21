#include "RoutineController.h"
#include "Routine.h"

RoutineController::RoutineController()
{
    routines = new AFArray<Routine*>;
    active = nullptr;
}

void RoutineController::tick()
{
    if (active) {
        active->tick();
    }
}

void RoutineController::addRoutine(Routine* routine)
{
    routines->add(routine);
}

void RoutineController::changeRoutine(const char* name)
{
    if (active) {
        active->after();
    }
    
    active = nullptr;

    while (routines->has_next()) {
        Routine* routine = routines->next();
        if (routine->getName() == name) {
            active = routine;
            break;
        }
    }

    if (active) {
        active->before();
    }
}