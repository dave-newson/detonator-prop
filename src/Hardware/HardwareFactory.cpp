#include "Hardware/Hardware.h"
#include "Led.h"
#include "RGBLed.h"
#include "Switch.h"
#include "Adafruit_SSD1306.h"
#include "Arduino.h"
#include "Beeper.h"
#include "Log.h"
#include "Module/DisplayModule.h"

#define PIN_KEYPAD_R1 5
#define PIN_KEYPAD_R2 3
#define PIN_KEYPAD_R3 2
#define PIN_KEYPAD_R4 7
#define PIN_KEYPAD_C1 4
#define PIN_KEYPAD_C2 9
#define PIN_KEYPAD_C3 6

#define PIN_LED_BUILTIN LED_BUILTIN
#define PIN_OLED_RESET 1

#define PIN_LED1_R 26
#define PIN_LED1_G 27
#define PIN_LED1_B 28

#define PIN_LED2_R 29
#define PIN_LED2_G 30
#define PIN_LED2_B 31

#define PIN_LED3_R 16
#define PIN_LED3_G 15
#define PIN_LED3_B 14

#define PIN_ARM_SWITCH 22

#define PIN_TRIGGER_SWITCH 21
#define PIN_TRIGGER_LED 20

#define PIN_BEEPER 10


// Cols/rows def for keypad
const byte ROWS = 4;
const byte COLS = 3;

// Define the symbols on the buttons of the keypads
const char hexaKeys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

// Pins relating to rols/cols on the keypad
byte rowPins[ROWS] = {PIN_KEYPAD_R1, PIN_KEYPAD_R2, PIN_KEYPAD_R3, PIN_KEYPAD_R4};
byte colPins[COLS] = {PIN_KEYPAD_C1, PIN_KEYPAD_C2, PIN_KEYPAD_C3}; 

Keypad keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

Led ledArmed(PIN_TRIGGER_LED);
Led ledDebug(PIN_LED_BUILTIN);

RGBLed led1(CATHODE, PIN_LED1_R, PIN_LED1_G, PIN_LED1_B);
RGBLed led2(CATHODE, PIN_LED2_R, PIN_LED2_G, PIN_LED2_B);
RGBLed led3(CATHODE, PIN_LED3_R, PIN_LED3_G, PIN_LED3_B);

Beeper beeper(PIN_BEEPER);

Switch armSwitch(PIN_ARM_SWITCH);
Switch triggerSwitch(PIN_TRIGGER_SWITCH);

Adafruit_SSD1306 display(PIN_OLED_RESET);

/**
 * Modules
 */
DisplayModule displayModule(&display);
KeypadModule keypadModule(&keypad, &beeper);

/**
 * Creates the Hardware struct
 */
Hardware HardwareFactory() {

    Hardware hardware = {};

    // LEDs
    hardware.ledArmed = &ledArmed;
    hardware.ledDebug = &ledDebug;

    // RGB LEDs
    hardware.led1 = &led1;
    hardware.led2 = &led2;
    hardware.led3 = &led3;

    // Hardware: OLED
    hardware.display = &displayModule;

    // Beeper
    hardware.beeper = &beeper;

    // Keypad
    hardware.keypad = &keypadModule;

    // Switches
    hardware.armed = &armSwitch;
    hardware.trigger = &triggerSwitch;

    return hardware;
}