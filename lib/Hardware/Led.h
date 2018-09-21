#ifndef LED_H
#define LED_H

class Led {

public:
    Led(int ledPin);
    void on();
    void off();
    bool isOn();

private:
    int pin;
    bool state;

};

#endif