
#include <Arduino.h>
#include <Hardware.h>
#include <Keypad.h>
#include <RGBLed.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

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

// Keypad
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// Hardware: LED
auto led1 = RGBLed(CATHODE, PIN_LED1_R, PIN_LED1_G, PIN_LED1_B);
auto led2 = RGBLed(CATHODE, PIN_LED2_R, PIN_LED2_G, PIN_LED2_B);
auto led3 = RGBLed(CATHODE, PIN_LED3_R, PIN_LED3_G, PIN_LED3_B);

// Hardware: OLED
auto display = Adafruit_SSD1306(PIN_OLED_RESET);


volatile bool isArmed = false;
volatile bool isTriggered = false;

void isrArmSwitch()
{
    isArmed = !isArmed;
}
void isrTriggerSwitch()
{
    isTriggered = !isTriggered;
}

/**
 * Setup devices
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

    // Setup: Display
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false);
    display.clearDisplay();

    // Setup: Arm Switch
    isArmed = digitalRead(PIN_ARM_SWITCH);
    attachInterrupt(digitalPinToInterrupt(PIN_ARM_SWITCH),isrArmSwitch,CHANGE);
    
    isTriggered = false;
    attachInterrupt(digitalPinToInterrupt(PIN_TRIGGER_SWITCH),isrTriggerSwitch,CHANGE);

    // Setup Complete
    digitalWrite(PIN_LED_BUILTIN, LOW);
}

/**
 * 
 */
void loop()
{

    // text display tests
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);

    if (isArmed && isTriggered) {
        led1.on(Color(255, 0, 0));
    }
    else if (isArmed) {
        display.setCursor(32,10);
        display.println("ARMED");
        display.invertDisplay(true);

        digitalWrite(PIN_TRIGGER_LED, HIGH);
    } 
    else {
        display.setCursor(42,10);
        display.println("SAFE");
        display.invertDisplay(false);
        
        digitalWrite(PIN_TRIGGER_LED, LOW);
    }

    display.display();    
    delay(100);
}
