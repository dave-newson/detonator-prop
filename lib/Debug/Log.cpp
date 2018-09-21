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

    void Log::log(const char* message)
    {
        Serial.write(message);
        Serial.write("\n");
    }
