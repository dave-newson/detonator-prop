#include "DeadManRoutine.h"
#include "DetonateRoutine.h"

DeadManRoutine::DeadManRoutine(Hardware* _hardware)
{
    hardware = _hardware;
}

void DeadManRoutine::before()
{
    hardware->display->setTextSize(2);
    hardware->display->setTextColor(WHITE);
    displayPrint("");

    // Reset trigger
    trigger = DIRTY;
}

void DeadManRoutine::tick()
{
    // When not "Armed", the device is in safe mode
    if (!hardware->armed->isOn()) {
        
        // Reset trigger to Dirty
        trigger = DIRTY;

        // Show "Safe"
        hardware->ledArmed->off();
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
        controller->changeRoutineByName(ROUTINE_DETONATE);
    }

    // Detect clean trigger state
    if (trigger == DIRTY && !hardware->trigger->isOn()) {
        trigger = CLEAN;
    }
    
    // Trigger is being held?
    if (trigger == HELD) {

        // Give a handy instruction
        displayPrint("HOLD");

    } else {

        // Just show the device is armed
        displayPrint("ARMED");
        hardware->ledArmed->on();
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