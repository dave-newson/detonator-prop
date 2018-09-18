/**
 * Hardware Prototype
 * 
 * Tests connectivity of hardware, provides output by Serial IO.
 */

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

#define PIN_BUZZER 9

#include <Arduino.h>
#include <RGBLed.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Keypad.h>

// Hardware: LED
auto led1 = RGBLed(CATHODE, PIN_LED1_R, PIN_LED1_G, PIN_LED1_B);
auto led2 = RGBLed(CATHODE, PIN_LED2_R, PIN_LED2_G, PIN_LED2_B);
auto led3 = RGBLed(CATHODE, PIN_LED3_R, PIN_LED3_G, PIN_LED3_B);

// Hardware: OLED
auto display = Adafruit_SSD1306(PIN_OLED_RESET);


// Cols/rows def for keypad
const byte ROWS = 4;
const byte COLS = 3;

//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
    {'#','0','*'},
    {'9','8','7'},
    {'6','5','4'},
    {'3','2','1'}
};

// Pins relating to rols/cols on the keypad
byte rowPins[ROWS] = {PIN_KEYPAD_R1, PIN_KEYPAD_R2, PIN_KEYPAD_R3, PIN_KEYPAD_R4};
byte colPins[COLS] = {PIN_KEYPAD_C1, PIN_KEYPAD_C2, PIN_KEYPAD_C3}; 

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 


/**
 * Test the LED on the switch
 */
void testSwitchLed()
{
    digitalWrite(PIN_TRIGGER_LED, HIGH);
    delay(500);
    digitalWrite(PIN_TRIGGER_LED, LOW);
    delay(500);
    digitalWrite(PIN_TRIGGER_LED, HIGH);
    delay(500);
    digitalWrite(PIN_TRIGGER_LED, LOW);
}

/**
 * Test RGB LEDs
 */
void testLeds()
{
    // Red
    led1.on(Color(255, 0, 0));
    delay(500);
    led2.on(Color(255, 0, 0));
    delay(500);
    led3.on(Color(255, 0, 0));
    delay(500);
    led1.off(); led2.off(); led3.off();

    // Green
    led1.on(Color(0, 255, 0));
    delay(500);
    led2.on(Color(0, 255, 0));
    delay(500);
    led3.on(Color(0, 255, 0));
    delay(500);
    led1.off(); led2.off(); led3.off();

    // Blue
    led1.on(Color(0, 0, 255));
    delay(500);
    led2.on(Color(0, 0, 255));
    delay(500);
    led3.on(Color(0, 0, 255));
    delay(500);
    led1.off(); led2.off(); led3.off();

    // White: All at once
    led1.on(Color(255, 255, 255));
    led2.on(Color(255, 255, 255));
    led3.on(Color(255, 255, 255));
    delay(1000);
    led1.off();
    led2.off();
    led3.off();
}

/**
 * Test the OLED display
 */
void testOled()
{
    // OLED
    // initialize with the I2C addr 0x3C (for the 128x32)
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false);
    display.clearDisplay();

    // Text
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

    display.write('H');
    display.write('I');
    display.display();

    // Clear after 2s
    delay(2000);
    display.clearDisplay();

}

/**
 * Tests the tone generating buzzer
 */
void testBuzzer()
{
    tone(PIN_BUZZER, 130.81);
    delay(300);
    tone(PIN_BUZZER, 174.61);
    delay(300);
    tone(PIN_BUZZER, 261.63);
    delay(300);
    noTone(PIN_BUZZER);

    tone(PIN_BUZZER, 261.63);
    delay(200);
    tone(PIN_BUZZER, 174.61);
    delay(200);
    tone(PIN_BUZZER, 130.81);
    delay(500);

    noTone(PIN_BUZZER);
}


/**
 * Setup Devices
 */
void setup()
{
    // Send built in LED high on boot.
    pinMode(PIN_LED_BUILTIN, OUTPUT);
    digitalWrite(PIN_LED_BUILTIN, HIGH);

    // Setup: Switches
    pinMode(PIN_ARM_SWITCH, INPUT_PULLUP);
    pinMode(PIN_TRIGGER_SWITCH, INPUT_PULLUP);
    pinMode(PIN_TRIGGER_LED, OUTPUT);
    

    // Setup: Buzzer
    pinMode(PIN_BUZZER, OUTPUT);

    // Setup: LEDs
    led1.setup();
    led2.setup();
    led3.setup();

    // Disable built in LED
    delay(1000);
    digitalWrite(PIN_LED_BUILTIN, LOW);

    // Boot-tests
    testLeds();
    testSwitchLed();
    testOled();
    testBuzzer();
}

bool armed = false;
bool trigger = false;

/**
 * Loop
 */
void loop()
{
    // TODO: Input tests

    armed = !digitalRead(PIN_ARM_SWITCH);
    trigger = !digitalRead(PIN_TRIGGER_SWITCH);

    // Reset
    led1.off();
    led2.off();

    if (armed) {
        led1.on(Color(255, 0, 0));
    }

    if (trigger) {
        led2.on(Color(255, 0, 0));
    }

    char customKey = keypad.getKey();
    if (customKey){
        display.write(customKey);
        display.display();
    }

}
