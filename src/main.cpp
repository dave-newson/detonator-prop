#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "Hardware/Hardware.h"
#include "Hardware/HardwareFactory.h"
#include "Chrono.h"
#include "RoutineController.h"
#include "Log.h"
#include "Routines/HardwareTestRoutine.h"
#include "Routines/DetonateRoutine.h"
#include "Routines/CountdownRoutine.h"
#include "Routines/DeadManRoutine.h"
#include "Routines/ManualTriggerRoutine.h"
#include "Routines/ModeSelectRoutine.h"

Hardware hardware = HardwareFactory();
RoutineController controller;
DetonateRoutine r1(&hardware);
HardwareTestRoutine r2(&hardware);
CountdownRoutine r3(&hardware);
DeadManRoutine r4(&hardware);
ManualTriggerRoutine r5(&hardware);
ModeSelectRoutine modeSelectRoutine(&hardware);

/**
 * Main entry point
 */
int main()
{
    // For debugging
    Serial1.begin(9600);
    // while(!Serial); // Enable only for debugging.

    Log::info("Booting!");
    
    Wire.begin();
    hardware.display->begin(SSD1306_SWITCHCAPVCC, 0x3C, true);

    Log::info("Setting up routines ...");
    controller.addRoutine(&modeSelectRoutine);
    controller.addRoutine(&r1);
    controller.addRoutine(&r2);
    controller.addRoutine(&r3);
    controller.addRoutine(&r4);
    controller.addRoutine(&r5);
    controller.setDefaultRoutine(&r2);
    
    Log::info("Setting up mode selection ...");
    modeSelectRoutine.addMode(&r2, "Hardware test");
    modeSelectRoutine.addMode(&r3, "Countdown");
    modeSelectRoutine.addMode(&r4, "Dead Man Trigger");
    modeSelectRoutine.addMode(&r5, "Manual Trigger");

    Log::info("Entering default routine ...");
    
    controller.changeRoutineToDefault();
    for (;;) {
        hardware.tick();
        controller.tick();
    }

}
