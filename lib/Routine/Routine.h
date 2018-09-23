#ifndef ROUTINE_H_
#define ROUTINE_H_

#include "RoutineController.h"
class RoutineController;

class Routine
{
    public:

        virtual const char* getName() =0;
        virtual void tick() = 0;
        virtual void before() = 0;
        virtual void after() = 0;

        void setController(RoutineController* _controller);

    protected:
        RoutineController* controller;
};

#endif