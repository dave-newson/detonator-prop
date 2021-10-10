#include "CountdownRoutine.h"
#include "Log.h"
#include "DetonateRoutine.h"

CountdownRoutine::CountdownRoutine(Hardware* _hardware)
{
    hardware = _hardware;
}

void CountdownRoutine::before()
{
    Log::info("Routine: Countdown Timer");

    // State resets
    timer1.restart();

    // Hardware
    hardware->reset();
    hardware->display->setTextSize(2);
    hardware->display->setTextColor(WHITE);

    // TODO: Port duration to "start" arg
    duration = 2 * 60; // 2min
}

void CountdownRoutine::tick()
{
    // Create 4 time segments: H:M:S:ms
    unsigned int timePart[4];

    // Convert elapsed to remaining, populate segments
    unsigned int remaining = (duration * 1000) - timer1.elapsed();
    timePart[0] = floor(remaining / 1000 / 60 / 60);
    remaining -= (timePart[0] * 1000 * 60 * 60);
    timePart[1] = floor(remaining / 1000 / 60);
    remaining -= (timePart[1] * 1000 * 60);
    timePart[2] = floor(remaining / 1000);
    remaining -= (timePart[2] * 1000);
    timePart[3] = floor(remaining);

    // Char Buffers (4 sets, of 2 length + 1 null)
    char timeSeg[4][3];

    // Convert time segments to characters (0 padded, len2)
    int i;
    for (i=0; i<4; i++) {
        snprintf(timeSeg[i], sizeof timeSeg[i], "%02d", timePart[i]);
    }

    // CLS
    hardware->display->setCursor(0,0);
    hardware->display->clearDisplay();

    // Display 
    hardware->display->print("\n     ");
    hardware->display->print(timeSeg[0]);
    hardware->display->print(":");
    hardware->display->print(timeSeg[1]);
    hardware->display->print(":");
    hardware->display->print(timeSeg[2]);
    hardware->display->print(":");
    hardware->display->print(timeSeg[3]);
    hardware->display->display();

    // Boom on fully lapsed
    if (timer1.elapsed() / 1000 >= duration) {
        controller->changeRoutineByName(ROUTINE_DETONATE);
    }
}

void CountdownRoutine::after()
{
    // Noop
}
