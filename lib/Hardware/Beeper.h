#ifndef BEEPER_H
#define BEEPER_H

class Beeper
{

public:
    Beeper(int beeperPin);

    void note(uint16_t freq);
    void note(uint16_t freq, uint32_t duration);
    void silence();

private:
    int pin;

};

#endif