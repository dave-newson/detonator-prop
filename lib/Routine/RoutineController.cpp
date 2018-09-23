#include "RoutineController.h"
#include "Routine.h"
#include "Log.h"

RoutineController::RoutineController()
{
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
    routine->setController(this);
    
    int space = -1;

    int i;
    for (i=0; i<MAX_ROUTINES; i++) {
        if (!routines[i]) {
            space = i;
            break;
        }
    }
    
    if (i == -1) {
        Log::error("Ran out of routine storage. Try raising the MAX_ROUTINES value");
        return;
    }

    routines[space] = routine;

}

Routine* RoutineController::getRoutineByName(const char* name)
{
    int i;
    for(i=0; i<MAX_ROUTINES; i++) {
        Routine* routine = routines[i];        
        if (routine && routine->getName() == name) {
            return routine;
        }
    }

    Log::error("Failed to find routine with specific name");
    Log::error(name);

    return nullptr;
}

void RoutineController::changeRoutineByName(const char* name)
{
    Routine* routine = getRoutineByName(name);

    if (routine) {
        changeRoutine(routine);
    }
}

void RoutineController::changeRoutine(Routine* routine)
{
    if (!routine) {
        Log::error("Cannot transition to null routine!");
    }

    // If an existing routine is running, call it's "after" sequence
    if (active) {
        active->after();
    }

    // Switch to new routine
    active = routine;

    // Execute "Before" of new routine
    active->before();
}
