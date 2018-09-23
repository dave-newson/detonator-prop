
#include "Arduino.h"
#include "Hardware.h"
#include "Hardware/HardwareFactory.h"
#include "Chrono.h"
#include "RoutineController.h"
#include "Log.h"
#include "Routines/HardwareTestRoutine.h"
#include "Routines/DetonateRoutine.h"

Hardware hardware = HardwareFactory();
RoutineController controller;
DetonateRoutine r1(&hardware);
HardwareTestRoutine r2(&hardware);

/**
 * Main entry point
 */
int main()
{
    // For debugger
    Serial.begin(9600);
    delay(1000);
    
    // Init hardware
    Log::info("Setting up hardware ...");
    

    // Start routine controller
    Log::info("Setting up routines ...");
    
    controller.addRoutine(&r1);
    controller.addRoutine(&r2);
    
    Log::info("Entering default routine ...");
    controller.changeRoutineByName(ROUTINE_HARDWARE_TEST);
    for (;;) {
        // Tick active routine forever
        controller.tick();
    }

}
