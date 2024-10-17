#include "TimedTask.h"


namespace seneca
{
void seneca::TimedTask::startClock()
{
    start = std::chrono::system_clock::now();
}

void seneca::TimedTask::stopClock()
{
    end = std::chrono::system_clock::now();
}



void seneca::TimedTask::addTask(char *str)
{
}

std::ostream &seneca::operator<<(std::ostream &os, TimedTask obj)
{
    // TODO: insert return statement here
}

}