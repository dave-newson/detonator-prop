#include "DetonateRoutine.h"
#include "Hardware.h"
#include "Log.h"

DetonateRoutine::DetonateRoutine(Hardware* _hardware)
{
    hardware = _hardware;
    returnRoutine = nullptr;
}

void DetonateRoutine::start(Routine* _returnAfter)
{
    Log::info("Transitoning to donate routine ...");
    returnRoutine = _returnAfter;
    controller->changeRoutine(this);
}

void DetonateRoutine::before()
{
    Log::info("Routine: Detonate");

    timer1.restart();
    hardware->display->setTextSize(2);
    hardware->display->setTextColor(WHITE);
    hardware->display->clearDisplay();
    hardware->display->setCursor(0,0);
    hardware->display->print(" DETONATE\n");
    hardware->display->display();

    // Reset stage
    stage = 0;
}

void DetonateRoutine::tick()
{
    int elapsed = timer1.elapsed();

    if (stage == 0) {
        stage++;
        Log::info("A");
        hardware->beeper->note(100);
    } else if (elapsed > 1000 && stage == 1) {
        stage++;
        Log::info("B");
        hardware->beeper->note(200);
    } else if (elapsed > 2000 && stage == 2) {
        stage++;
        Log::info("C");
        hardware->beeper->note(300);
	} else if (elapsed > 3000 && stage == 3) {
        Log::info("Done");
        controller->changeRoutine(returnRoutine);
    }

}

void DetonateRoutine::after()
{
    hardware->display->clearDisplay();
    hardware->display->display();
    hardware->beeper->silence();
    returnRoutine = nullptr;
}
