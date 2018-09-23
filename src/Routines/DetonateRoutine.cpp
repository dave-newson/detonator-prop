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
    timer2.restart();
    
    // LED state
    ledState = false;
    hardware->led1->off();
    hardware->led2->off();
    hardware->led3->off();

    // Prepare screen
    hardware->display->setTextSize(2);
    hardware->display->setTextColor(WHITE);

    // Reset stage
    stage = 0;
}

void DetonateRoutine::tick()
{
    int elapsed = timer1.elapsed();

    if (timer2.hasPassed(500)) {
        timer2.restart();
        ledState = !ledState;

        if (ledState) {
            hardware->led1->on(Color(255, 255, 0));
            hardware->led2->on(Color(255, 255, 0));
            hardware->led3->on(Color(255, 255, 0));
        } else {
            hardware->led1->off();
            hardware->led2->off();
            hardware->led3->off();
        }
    }

    if (stage == 0) {
        stage++;

        hardware->display->clearDisplay();
        hardware->display->setCursor(0,0);        
        hardware->display->print(" DETONATE ");
        hardware->display->display();

        hardware->beeper->note(100);
    } else if (elapsed > 1000 && stage == 1) {
        stage++;

        hardware->display->clearDisplay();
        hardware->display->setCursor(0,0);
        hardware->display->print("!DETONATE!");
        hardware->display->display();

        hardware->beeper->note(200);
    } else if (elapsed > 2000 && stage == 2) {
        stage++;

        hardware->display->clearDisplay();
        hardware->display->setCursor(0,0);        
        hardware->display->print(" DETONATE ");
        hardware->display->display();

        hardware->beeper->note(300);
	} else if (elapsed > 3000 && stage == 3) {

        hardware->beeper->silence();

        if (returnRoutine) {
            controller->changeRoutine(returnRoutine);
        }
    }

}

void DetonateRoutine::after()
{
    hardware->display->clearDisplay();
    hardware->display->display();
    returnRoutine = nullptr;
}
