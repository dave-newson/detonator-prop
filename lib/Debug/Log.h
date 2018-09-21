#ifndef DEBUG_LOG_H_
#define DEBUG_LOG_H_

class Log {

public: 

    static void markOn();
    static void markOff();
    static void log(const char* message);

};

#endif