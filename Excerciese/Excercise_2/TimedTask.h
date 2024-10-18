#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <iostream>
#include <chrono>
#include <string>

namespace seneca
{
    constexpr size_t Max = 10;
    class TimedTask
    {
        size_t numberOfRecords{};
        std::chrono::time_point<std::chrono::steady_clock> start;
        std::chrono::time_point<std::chrono::steady_clock> end;
        struct task 
        {
            std::string task_name{};
            std::string time_unit{};
            std::chrono::steady_clock::duration duration;
        } tasks[Max];

        public:
            void startClock();
            void stopClock();
            void addTask(const char* str);
            friend std::ostream &operator <<(std::ostream& os, const TimedTask &obj);
    };


}


#endif