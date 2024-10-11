#ifndef TIMEMONITOR_H
#define TIMEMONITOR_H

#include <chrono>
#include <string>
#include "event.h"

class TimeMonitor {

    std::chrono::time_point<std::chrono::high_resolution_clock> startTime; 
    std::string eventName; 

public:
    TimeMonitor(); 
    void startEvent(const char* name); 
    Event stopEvent()const; 
};


#endif
