#include "TimedTask.h"
#include <iomanip>

namespace seneca
{

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
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        if (numberOfRecords < Max)
        {
            this->tasks[numberOfRecords].task_name = str;
            this->tasks[numberOfRecords].time_unit = "nanoseconds";
            this->tasks[numberOfRecords].duration = duration;
            numberOfRecords++;
        }
    }

    std::ostream &operator<<(std::ostream &os, const TimedTask& obj)
    {
        os << "Execution Times:\n";
        os << "--------------------------\n";
        for (size_t count = 0; count < obj.numberOfRecords; ++count)
        {
            os << obj.tasks[count].task_name << " "
               << obj.tasks[count].duration.count() << " "
               << obj.tasks[count].time_unit << std::endl;
        }
        os << "--------------------------\n";

        return os;
    }

}