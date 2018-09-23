#include "ModeSelectRoutine.h"
#include "Log.h"

ModeSelectRoutine::ModeSelectRoutine(Hardware* _hardware)
{
    hardware = _hardware;
}

void ModeSelectRoutine::before()
{
    hardware->display->setTextSize(1);
    hardware->display->setTextColor(WHITE);
    displayPrint("");

    // Reset mode selection to Zero
    selected = 0;
    updateSelection();
}

void ModeSelectRoutine::tick()
{
    char key = hardware->keypad->getKey();

    // On * key: Change routine
    if (key == '*') {
        selected++;

        // On overflow of available modes, reset to zero.
        if (!modes[selected].routine) {
            selected = 0;
        }

        updateSelection();
    }

    // On # Key: Execute routine
    if (key == '#') {
        controller->changeRoutine(modes[selected].routine);
    }
}

void ModeSelectRoutine::after()
{
    // Noop
}

void ModeSelectRoutine::addMode(Routine* routine, const char* title)
{
    // Locate an empty mode slot
    int space = -1;
    int i = 0;
    for (i=0; i<MAX_MODES; i++) {
        if (!modes[i].routine) {
            space = i;
            break;
        }
    }

    // Prevent overflowing storage
    if (i == -1) {
        Log::error("Exhausted Mode storage: Try raising MAX_MODES value.");
        return;
    }

    // Store
    modes[space].routine = routine;;
    modes[space].title = title;
}

void ModeSelectRoutine::displayPrint(const char* message)
{
    hardware->display->clearDisplay();
    hardware->display->setCursor(0,0);
    hardware->display->print("-- MODE SELECTION --\n\n");
    hardware->display->print(selected + 1);
    hardware->display->print(" ");
    hardware->display->print(message);
    hardware->display->display();
}

void ModeSelectRoutine::updateSelection()
{
    // Show name of the mode
    displayPrint(modes[selected].title);
}