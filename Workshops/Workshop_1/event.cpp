#include "event.h"
#include <iomanip>

Event::Event()
{
    event_name = "";
    duration = std::chrono::nanoseconds(0);
}

Event::Event(std::string eventName, std::chrono::nanoseconds newDuration):event_name(eventName),duration(newDuration)
{
}

int getWidth(const std::string unit) 
{
    if (unit == "seconds") {
        return 2;
    }
    else if (unit == "milliseconds") {
        return 5;
    }
    else if (unit == "microseconds") {
        return 8;
    }
    else {
        return 11;
    }
}

double getDuration(const std::chrono::nanoseconds& duration, const std::string unit) 
{
    if (unit == "seconds") 
    {
        return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
    }
    else if (unit == "milliseconds") 
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }
    else if (unit == "microseconds") 
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    }
    else return duration.count();
}


std::ostream &operator<<(std::ostream& os, const Event &event)
{
    // TODO: insert return statement here
    static int counter = 0;
    std::string time_units = g_settings.m_time_units;

    os << std::setw(2) << counter << ": "
        << std::setw(40) << event.event_name << " -> "
        << std::setw(getWidth(time_units)) << getDuration(event.duration, time_units) << " " << time_units;
}
