#include "HardwareTestRoutine.h"
#include "hardware.h"
#include "RGBLed.h"
#include "Log.h"

HardwareTestRoutine::HardwareTestRoutine(Hardware* _hardware)
{
    hardware = _hardware;
    timer1 = new Chrono();
    timer2 = new Chrono();
    timer3 = new Chrono();
    colorSlide = 0;
}

void HardwareTestRoutine::before()
{
    Log::log("Started hardware debug routine");

    // text display tests
    resetDisplay();

    hardware->led1->off();
    hardware->led2->off();
    hardware->led3->off();

    hardware->ledArmed->off();
}

void HardwareTestRoutine::tick()
{
    // LED Armed (blinks)
    if (timer1->hasPassed(1000) ) {
        timer1->restart();
        
        if (hardware->ledArmed->isOn()) {
            hardware->ledArmed->off();
        } else {
            hardware->ledArmed->on();
        }
    }

    // LED Debug (blinks)
    if (timer2->hasPassed(500) ) {
        timer2->restart();
        
        if (hardware->ledDebug->isOn()) {
            hardware->ledDebug->off();
        } else {
            hardware->ledDebug->on();
        }
    }

    // LED 3 (cycles)
    if (timer3->hasPassed(1000) ) {
        timer3->restart();

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
        hardware->led1->on(Color(255, 255, 255));
        hardware->led2->on(Color(255, 255, 255));
        hardware->led3->on(Color(255, 255, 255));

        hardware->beeper->note(500);
        resetDisplay();

    } else {

        hardware->beeper->silence();

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

void HardwareTestRoutine::resetDisplay()
{
    hardware->display->setTextSize(1);
    hardware->display->setTextColor(WHITE);
    hardware->display->clearDisplay();
    hardware->display->setCursor(0,0);
    hardware->display->print("TEST MODE\n");
    hardware->display->display();
}