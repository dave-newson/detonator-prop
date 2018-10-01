#ifndef DISPLAY_MODULE_H_
#define DISPLAY_MODULE_H_

#include "Adafruit_SSD1306.h"

class DisplayModule
{

public:
    DisplayModule(Adafruit_SSD1306* display);
    void begin(uint8_t vccstate, uint8_t i2caddr, bool reset) {};
    void clearDisplay() {};
    void display() {};
    void setCursor(int x, int y) {};
    void print(int message) {};
    void print(char* message) {};
    void print(const char* message) {};
    void write(char message) {};
    void setTextSize(int size) {};
    void setTextColor(int color) {};
    


private:
    Adafruit_SSD1306* _display;
};

#endif