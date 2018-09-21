#ifndef ROUTINE_CONTROLLER_H_
#define ROUTINE_CONTROLLER_H_

#include "AFArray.h"
#include "Routine.h"

class RoutineController
{

    public:
        RoutineController();

        /**
         * Add a routine to the Controller
         */
        void addRoutine(Routine* routine);

        /**
         * Call tick for the active routine
         */
        void tick();

        /**
         * Change to a new routine
         */
        void changeRoutine(const char* name);

    private:

        /**
         * Collection of available routines
         */
        AFArray<Routine*>* routines;

        Routine* active;
};

#endif