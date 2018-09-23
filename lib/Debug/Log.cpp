#include "Log.h"
#include "Arduino.h"

void Log::markOn()
{
    digitalWrite(LED_BUILTIN, HIGH);
}

void Log::markOff()
{
    digitalWrite(LED_BUILTIN, LOW);
}

void Log::info(const char* message)
{
    Serial.write("INFO: ");
    Serial.write(message);
    Serial.write("\n");
    Serial.flush();
}

void Log::error(const char* message)
{
    Serial.write("ERROR: ");
    Serial.write(message);
    Serial.write("\n");
    Serial.flush();
}

