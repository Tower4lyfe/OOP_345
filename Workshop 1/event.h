#ifndef EVENT_H
#define EVENT_H
#include <iostream>
#include <chrono>

class Event
{
    std::string event_name;
    std::chrono::nanoseconds duration;

    public:
    Event();
    friend std::ostream & operator <<(std::ostream os, const Event & event);
};

#endif