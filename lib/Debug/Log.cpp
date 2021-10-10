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
    Serial1.write("INFO: ");
    Serial1.write(message);
    Serial1.write("\n");
    Serial1.flush();
}

void Log::error(const char* message)
{
    Serial1.write("ERROR: ");
    Serial1.write(message);
    Serial1.write("\n");
    Serial1.flush();
}

