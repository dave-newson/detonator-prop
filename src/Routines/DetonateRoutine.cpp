#include "DetonateRoutine.h"
#include "Hardware/Hardware.h"
#include "Log.h"

DetonateRoutine::DetonateRoutine(Hardware* _hardware)
{
    hardware = _hardware;
    returnRoutine = nullptr;
}

void DetonateRoutine::start(Routine* _returnAfter = nullptr)
{
    Log::info("Transitoning to donate routine ...");
    returnRoutine = _returnAfter;
    controller->changeRoutine(this);
}

void DetonateRoutine::before()
{
    Log::info("Routine: Detonate");
   
    // State resets
    timer1.restart();
    timer2.restart();

    // Hardware reset
    hardware->reset();

    hardware->display->clearDisplay();
    hardware->display->setCursor(0,0);
    hardware->display->setTextSize(2);
    hardware->display->print("DETONATE");
    hardware->display->display();
}

void DetonateRoutine::tick()
{

    if (!timer2.hasPassed(100)) {
        hardware->led1->on(Color(255, 255, 255));
        hardware->led2->on(Color(255, 255, 255));
        hardware->led3->on(Color(255, 255, 255));
        hardware->beeper->note(60);
    } else if (!timer2.hasPassed(200)) {
        hardware->led1->off();
        hardware->led2->off();
        hardware->led3->off();
        hardware->beeper->silence();
    } else if (!timer2.hasPassed(300)) {
        hardware->led1->on(Color(255, 255, 255));
        hardware->led2->on(Color(255, 255, 255));
        hardware->led3->on(Color(255, 255, 255));
        hardware->beeper->note(100);
    } else if (!timer2.hasPassed(400)) {
        hardware->led1->off();
        hardware->led2->off();
        hardware->led3->off();
        hardware->beeper->silence();
    } else {
        timer2.restart();
    }
    
    if (timer1.hasPassed(2000)) {
        if (returnRoutine) {
            controller->changeRoutine(returnRoutine);
        } else {
            controller->changeRoutineToDefault();
        }
    }

}

void DetonateRoutine::after()
{
    hardware->reset();
    returnRoutine = nullptr;
}
