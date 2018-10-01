#ifndef ROUTINE_CONTROLLER_H_
#define ROUTINE_CONTROLLER_H_

#include "Routine.h"

#define MAX_ROUTINES 10

class Routine;

class RoutineController
{

    public:
        RoutineController();

        /**
         * Add a routine to the Controller
         */
        void addRoutine(Routine* routine);

        void setDefaultRoutine(Routine* routine);

        /**
         * Call tick for the active routine
         */
        void tick();

        /**
         * Change to a new routine
         */
        void changeRoutineByName(const char* name);

        /**
         * Change to new specific routine
         */
        void changeRoutine(Routine* routine);

        /**
         * Change to default routine
         */
        void changeRoutineToDefault();

        /**
         * Fetch a routine by its name
         */
        Routine* getRoutineByName(const char* name);

    private:

        /**
         * Collection of available routines
         */
        Routine* routines[MAX_ROUTINES];

        /**
         * Pointer to active routine
         */
        Routine* active = nullptr;

        /**
         * Pointer to default routine
         */
        Routine* defaultRoutine = nullptr;
};

#endif