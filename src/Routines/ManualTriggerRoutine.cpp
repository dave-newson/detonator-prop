#include "ManualTriggerRoutine.h"
#include "DetonateRoutine.h"

ManualTriggerRoutine::ManualTriggerRoutine(Hardware* _hardware)
{
    hardware = _hardware;
}

void ManualTriggerRoutine::before()
{
    hardware->display->setTextSize(2);
    hardware->display->setTextColor(WHITE);
    displayPrint("");

    // Reset trigger
    trigger = DIRTY;
}

void ManualTriggerRoutine::tick()
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
    // Just show the device is armed
    displayPrint("ARMED");
    hardware->ledArmed->on();

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
    // Noop
}

void ManualTriggerRoutine::displayPrint(const char* message)
{
    hardware->display->clearDisplay();
    hardware->display->setCursor(0,0);
    hardware->display->print(message);
    hardware->display->display();
}