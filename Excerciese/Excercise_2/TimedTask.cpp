#include "TimedTask.h"

seneca::TimedTask::TimedTask(TimedTask &copy)
{
    if(this!=&copy)
        *this = copy;

}

seneca::TimedTask &seneca::TimedTask::operator=(const TimedTask &copy)
{
    if(this != &copy)
    {
        numberOfRecords = copy.numberOfRecords;
        start = copy.start;
        end = copy.end;
        for(size_t count = 0; count < Max; ++count)
        {
            tasks[count].duration = copy.tasks[count].duration;
            tasks[count].task_name = copy.tasks[count].task_name;
            tasks[count].time_unit = copy.tasks[count].time_unit;
        }
    }

    return *this;
}


void seneca::TimedTask::startClock()
{
    start = std::chrono::steady_clock::now();
}

void seneca::TimedTask::stopClock()
{
    end = std::chrono::steady_clock::now();
}



void seneca::TimedTask::addTask(const char *str)
{
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
    if (numberOfRecords < Max)
    {
        tasks[numberOfRecords].task_name = str;
        tasks[numberOfRecords].time_unit = "nanoseconds";
        tasks[numberOfRecords].duration = duration;
        numberOfRecords++;
    }
}

std::ostream &seneca::operator<<(std::ostream &os,const TimedTask obj)
{
    os << "Execution Times:\n";
    os << "--------------------------\n";
    for(size_t count = 0; count < obj.numberOfRecords; ++count)
    {
        os << obj.tasks[count].task_name << " "
        << obj.tasks[count].duration.count() << " " 
        << obj.tasks[count].time_unit << std::endl;
    }
    os << "--------------------------\n";
}
