#include "ManualTriggerRoutine.h"
#include "DetonateRoutine.h"
#include "Log.h"

ManualTriggerRoutine::ManualTriggerRoutine(Hardware* _hardware)
{
    hardware = _hardware;
}

void ManualTriggerRoutine::before()
{
    Log::info("Routine: Manual Trigger");

    // State resets
    trigger = DIRTY;

    // Timers
    timer1.restart();

    // Hardware reset
    hardware->reset();
    hardware->display->setTextSize(4);
    hardware->display->setTextColor(WHITE);
}

void ManualTriggerRoutine::tick()
{
// When not "Armed", the device is in safe mode
    if (!hardware->armed->isOn()) {
        
        // Reset trigger to Dirty
        trigger = DIRTY;

        // Show "Safe"
        hardware->ledArmed->off();
        displayPrint("SAFE", 20);
        hardware->led1->on(Color(0, 128, 0));
        hardware->led2->on(Color(0, 128, 0));
        hardware->led3->on(Color(0, 128, 0));

        // No other operation
        return;
    }

    // -- WHEN ARMED --

    // Just show the device is armed
    displayPrint("ARMED", 8);
    hardware->ledArmed->on();
    hardware->led1->on(Color(255, 0, 0));
    hardware->led2->on(Color(255, 0, 0));
    hardware->led3->on(Color(255, 0, 0));

    // Listen for first press of the Trigger
    if (trigger == CLEAN && hardware->trigger->isOn()) {
        controller->changeRoutineByName(ROUTINE_DETONATE);
    }

    // Detect clean trigger state
    if (trigger == DIRTY && !hardware->trigger->isOn()) {
        trigger = CLEAN;
    }
}

void ManualTriggerRoutine::after()
{
    hardware->reset();
}

void ManualTriggerRoutine::displayPrint(const char* message, int offset = 8)
{
    hardware->display->clearDisplay();
    hardware->display->setCursor(offset,0);
    hardware->display->print(message);
    hardware->display->display();
}
