#include "DisplayModule.h"
#include "Log.h"
#include "Wire.h"

DisplayModule::DisplayModule(Adafruit_SSD1306* display)
{
    _display = display;
}

void DisplayModule::clearDisplay()
{
    if (!_display) return;
    _display->clearDisplay();
}

void DisplayModule::begin(uint8_t vccstate, uint8_t i2caddr, bool reset)
{
    Wire.beginTransmission(i2caddr);
    byte error = Wire.endTransmission();

    if (error != 0) {
        Log::error("Failed to connect to display");
        _display = nullptr;
        return;
    }

    _display->begin(vccstate, i2caddr, reset);
    clearDisplay();
    display();
}

void DisplayModule::display()
{
    if (!_display) return;
    _display->display();
}

void DisplayModule::setCursor(int x, int y)
{
    if (!_display) return;
    _display->setCursor(x, y);
}

void DisplayModule::print(int message)
{
    if (!_display) return;
    _display->print(message);
}

void DisplayModule::print(char* message)
{
    if (!_display) return;
    _display->print(message);
}

void DisplayModule::print(const char* message)
{
    if (!_display) return;
    _display->print(message);
}

void DisplayModule::write(char message)
{
    if (!_display) return;
    _display->write(message);
}

void DisplayModule::setTextSize(int size)
{
    if (!_display) return;
    _display->setTextSize(size);
}

void DisplayModule::setTextColor(int color)
{
    if (!_display) return;
    _display->setTextColor(color);
}

void DisplayModule::drawPixel(int16_t x, int16_t y, uint16_t color)
{
    if (!_display) return;
    _display->drawPixel(x, y, color);
}

void DisplayModule::invertDisplay(uint8_t i)
{
    if (!_display) return;
    _display->invertDisplay(i);
}
