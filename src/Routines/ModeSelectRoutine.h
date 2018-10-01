#ifndef MODE_SELECT_ROUTINE_H_
#define MODE_SELECT_ROUTINE_H_

#include "Hardware/Hardware.h"
#include "Routine.h"
#include "Chrono.h"

#define ROUTINE_MODE_SELECT "mode_select"
#define MAX_MODES 10

class ModeSelectRoutine : public Routine
{

    struct Mode {
        const char* title;
        Routine* routine;
    };

public:
    ModeSelectRoutine(Hardware* _hardware);
    const char* getName() { return ROUTINE_MODE_SELECT; };
    void tick();
    void before();
    void after();

    void addMode(Routine* routine, const char* title);

private:
    Hardware* hardware;
    
    /**
     * Array of available modes
     */
    Mode modes[MAX_MODES];
    
    /**
     * Current selected mode idx
     */
    int selected;

    void displayPrint(const char* message);
    void updateSelection();
};

#endif