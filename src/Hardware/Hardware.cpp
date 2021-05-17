#include "Hardware.h"

void Hardware::tick()
{
    keypad->tick();
}

void Hardware::reset()
{
    led1->off();
    led2->off();
    led3->off();
    ledArmed->off();
    
    display->clearDisplay();
    display->setCursor(0,0);
    display->drawPixel(2, 2, WHITE);
    display->display();
}
