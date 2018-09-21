#include "Hardware.h"
#include "Led.h"
#include "RGBLed.h"
#include "Switch.h"
#include "Adafruit_SSD1306.h"
#include "Arduino.h"
#include "Beeper.h"

#define PIN_KEYPAD_R1 3
#define PIN_KEYPAD_R2 8
#define PIN_KEYPAD_R3 7
#define PIN_KEYPAD_R4 5
#define PIN_KEYPAD_C1 4
#define PIN_KEYPAD_C2 2
#define PIN_KEYPAD_C3 6

#define PIN_LED_BUILTIN LED_BUILTIN
#define PIN_OLED_RESET 1

#define PIN_LED1_R 26
#define PIN_LED1_G 27
#define PIN_LED1_B 28

#define PIN_LED2_R 31
#define PIN_LED2_G 30
#define PIN_LED2_B 29

#define PIN_LED3_R 14
#define PIN_LED3_G 15
#define PIN_LED3_B 16

#define PIN_ARM_SWITCH 22

#define PIN_TRIGGER_SWITCH 21
#define PIN_TRIGGER_LED 20

#define PIN_BEEPER 9


// Cols/rows def for keypad
const byte ROWS = 4;
const byte COLS = 3;

// Define the symbols on the buttons of the keypads
// Board was rotated 180', hence backwards representation here.
const char hexaKeys[ROWS][COLS] = {
    {'#','0','*'},
    {'9','8','7'},
    {'6','5','4'},
    {'3','2','1'}
};

// Pins relating to rols/cols on the keypad
byte rowPins[ROWS] = {PIN_KEYPAD_R1, PIN_KEYPAD_R2, PIN_KEYPAD_R3, PIN_KEYPAD_R4};
byte colPins[COLS] = {PIN_KEYPAD_C1, PIN_KEYPAD_C2, PIN_KEYPAD_C3}; 


/**
 * Creates the Hardware struct
 */
Hardware HardwareFactory() {

    Hardware hardware = {};

    // LEDs
    hardware.ledArmed = new Led(PIN_TRIGGER_LED);
    hardware.ledDebug = new Led(PIN_LED_BUILTIN);

    // RGB LEDs
    hardware.led1 = new RGBLed(CATHODE, PIN_LED1_R, PIN_LED1_G, PIN_LED1_B);
    hardware.led2 = new RGBLed(CATHODE, PIN_LED2_R, PIN_LED2_G, PIN_LED2_B);
    hardware.led3 = new RGBLed(CATHODE, PIN_LED3_R, PIN_LED3_G, PIN_LED3_B);

    // Hardware: OLED
    hardware.display = new Adafruit_SSD1306(PIN_OLED_RESET);
    hardware.display->begin(SSD1306_SWITCHCAPVCC, 0x3C, false);
    hardware.display->clearDisplay();
    hardware.display->display();


    hardware.beeper = new Beeper(PIN_BEEPER);

    // Keypad
    hardware.keypad = new Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
    delay(100);
    hardware.keypad->getKey();

    // Switches
    hardware.armed = new Switch(PIN_ARM_SWITCH);
    hardware.trigger = new Switch(PIN_TRIGGER_SWITCH);

    return hardware;
}