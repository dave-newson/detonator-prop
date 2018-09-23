#ifndef DEBUG_LOG_H_
#define DEBUG_LOG_H_

class Log {

public: 

    static void markOn();
    static void markOff();
    static void info(const char* message);
    static void error(const char* message);
    
};

#endif