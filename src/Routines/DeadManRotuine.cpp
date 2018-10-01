#include "DeadManRoutine.h"
#include "DetonateRoutine.h"
#include "Log.h"

DeadManRoutine::DeadManRoutine(Hardware* _hardware)
{
    hardware = _hardware;
}

void DeadManRoutine::before()
{
    Log::info("Routine: Dead Man");

    // Hardware resets
    hardware->reset();
    hardware->display->setTextSize(2);
    hardware->display->setTextColor(WHITE);

    // Timers
    timer1.restart();
    timer2.stop();
    timer3.stop();

    // State reset
    trigger = DIRTY;
}

void DeadManRoutine::tick()
{
    // Read keypad so it does its things
    hardware->keypad->getKey();

    // When not "Armed", the device is in safe mode
    if (!hardware->armed->isOn()) {
        
        // Reset trigger to Dirty
        trigger = DIRTY;

        // Disable detonate timer
        timer2.stop();

        // Show "Safe"
        hardware->ledArmed->off();
        
        if (!timer3.isRunning()) {
            timer3.restart();
        }

        if (!timer3.hasPassed(3000)) {
            hardware->led1->on(Color(0,255,0));
            hardware->led2->on(Color(0,255,0));
            hardware->led3->on(Color(0,255,0));    
        } else {
            hardware->led1->off();
            hardware->led2->off();
            hardware->led3->off();
        }

        displayPrint("SAFE");

        // No other operation
        return;
    }

    // -- WHEN ARMED --

    // Listen for first press of the Trigger
    if (trigger == CLEAN && hardware->trigger->isOn()) {
        trigger = HELD;
    }

    // Listen for release of trigger
    if (trigger == HELD && !hardware->trigger->isOn()) {
        if (!timer2.isRunning()) {
            timer2.restart();
            timer2.start();
        }

        if (timer2.hasPassed(100)) {
            DetonateRoutine* detonate = (DetonateRoutine*) controller->getRoutineByName(ROUTINE_DETONATE);
            detonate->start(this);
        }
    }

    // Detect clean trigger state
    if (trigger == DIRTY && !hardware->trigger->isOn()) {
        trigger = CLEAN;
    }
    
    // Trigger is being held?
    if (trigger == HELD) {

        // Give a handy instruction
        displayPrint("HOLD");
        
        // Flash LEDs every X seconds.
        if (timer1.hasPassed(250)) {
            timer1.restart();

            if (hardware->ledArmed->isOn()) {
                hardware->ledArmed->off();
                hardware->led1->on(Color(255, 0, 0));
                hardware->led2->off();
            } else {
                hardware->ledArmed->on();
                hardware->led1->off();
                hardware->led2->on(Color(255, 0, 0));
            }
        }

    } else {

        // Just show the device is armed
        displayPrint("ARMED");
        hardware->ledArmed->on();

        hardware->led1->on(Color(255, 255, 0));
        hardware->led2->on(Color(255, 255, 0));
        hardware->led3->on(Color(255, 255, 0));

        timer3.stop();
    }
}

void DeadManRoutine::after()
{
    // Noop
}

void DeadManRoutine::displayPrint(const char* message)
{
    hardware->display->clearDisplay();
    hardware->display->setCursor(0,0);
    hardware->display->print(message);
    hardware->display->display();
}