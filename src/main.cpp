
#include "Arduino.h"
#include "Hardware.h"
#include "Hardware/HardwareFactory.h"
#include "Chrono.h"
#include "RoutineController.h"
#include "Routines/HardwareTestRoutine.h"
#include "Log.h"

/**
 * Main entry point
 */
int main()
{
    // For debugger
    Serial.begin(9600);
    delay(2000);
    
    // Init hardware
    Log::log("Waking up..");
    Hardware hardware = HardwareFactory();

    // Start routine controller
    Log::log("Starting routine ...");
    RoutineController* controller = new RoutineController();
    controller->addRoutine(new HardwareTestRoutine(&hardware));
    controller->changeRoutine(ROUTINE_HARDWARE_TEST);

    // Tick active routine
    for (;;) {
        controller->tick();
    }

}
