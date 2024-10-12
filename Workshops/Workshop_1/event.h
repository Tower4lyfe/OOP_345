#ifndef EVENT_H
#define EVENT_H

#include "settings.h"
#include <iostream>
#include <chrono>

class Event
{
private:
    std::string event_name;
    std::chrono::nanoseconds duration;

public:
    Event();
    Event(std::string eventName, std::chrono::nanoseconds newDuration);
    friend std::ostream & operator <<(std::ostream& os, const Event & event);
};

#endif