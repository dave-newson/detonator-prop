#include "HardwareTestRoutine.h"
#include "Hardware/hardware.h"
#include "RGBLed.h"
#include "Log.h"
#include "DetonateRoutine.h"

HardwareTestRoutine::HardwareTestRoutine(Hardware* _hardware)
{
    hardware = _hardware;
}

void HardwareTestRoutine::before()
{
    Log::info("Routine: Hardware test");

    // State Resets
    colorSlide = 0;
    timer1.restart();
    timer2.restart();
    timer3.restart();

    // Hardware reset    
    hardware->reset();
    hardware->display->setTextSize(1);
    hardware->display->setTextColor(WHITE);

    // Screen text (never changes)
    hardware->display->print("TEST MODE\n");
    hardware->display->display();
}

void HardwareTestRoutine::tick()
{
    // LED Armed (blinks)
    if (timer1.hasPassed(1000) ) {
        timer1.restart();
        
        if (hardware->ledArmed->isOn()) {
            hardware->ledArmed->off();
        } else {
            hardware->ledArmed->on();
        }
    }

    // LED Debug (blinks)
    if (timer2.hasPassed(500) ) {
        timer2.restart();
        
        if (hardware->ledDebug->isOn()) {
            hardware->ledDebug->off();
        } else {
            hardware->ledDebug->on();
        }
    }

    // LED 3 (cycles)
    if (timer3.hasPassed(1000) ) {
        timer3.restart();

        // Increment/reset
        colorSlide = (colorSlide > 3 ? 1 : colorSlide + 1);

        // Colorise LED
        hardware->led3->on(Color(
            (colorSlide == 1) ? 255 : 0,
            (colorSlide == 2) ? 255 : 0,
            (colorSlide == 3) ? 255 : 0
        ));
    }

    // Trigger Switch, buzzer, Led 1 & 2
    if (hardware->armed->isOn() && hardware->trigger->isOn()) {
        DetonateRoutine* detonate = (DetonateRoutine*) controller->getRoutineByName(ROUTINE_DETONATE);
        detonate->start(this);

    } else {

        if (hardware->armed->isOn()) {
            hardware->led1->on(Color(255, 0, 0));
        } else {
            hardware->led1->on(Color(0, 255, 0));
        }

        if (hardware->trigger->isOn()) {
            hardware->led2->on(Color(255, 0, 0));
        } else {
            hardware->led2->on(Color(0, 255, 0));
        }
    }

    // Keypad, OLED
    char customKey = hardware->keypad->getKey();
    
    if (customKey) {
        hardware->display->write(customKey);
        hardware->display->display();
    }

}
