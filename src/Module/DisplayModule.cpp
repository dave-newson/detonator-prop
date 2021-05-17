#include "DisplayModule.h"

DisplayModule::DisplayModule(Adafruit_SSD1306* display)
{
    _display = display;
}

void DisplayModule::clearDisplay()
{
    _display->clearDisplay();
}

void DisplayModule::begin(uint8_t vccstate, uint8_t i2caddr, bool reset)
{
    _display->begin(vccstate, i2caddr, reset);
}

void DisplayModule::display()
{
    _display->display();
}

void DisplayModule::setCursor(int x, int y)
{
    _display->setCursor(x, y);
}

void DisplayModule::print(int message)
{
    _display->print(message);
}

void DisplayModule::print(char* message)
{
    _display->print(message);
}

void DisplayModule::print(const char* message)
{
    _display->print(message);
}

void DisplayModule::write(char message)
{
    _display->write(message);
}

void DisplayModule::setTextSize(int size)
{
    _display->setTextSize(size);
}

void DisplayModule::setTextColor(int color)
{
    _display->setTextColor(color);
}

void DisplayModule::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    _display->drawPixel(x, y, color);
}

void DisplayModule::invertDisplay(uint8_t i)
{
    _display->invertDisplay(i);
}
