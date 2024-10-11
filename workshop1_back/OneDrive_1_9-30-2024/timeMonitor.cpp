#include "TimeMonitor.h"


TimeMonitor::TimeMonitor() :eventName("")  {}


void TimeMonitor::startEvent(const char* name) {
    eventName = name;
    startTime = std::chrono::high_resolution_clock::now(); 

}

Event  TimeMonitor :: stopEvent()const {

    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

    
    Event event(eventName, duration);
    return event; 
}
