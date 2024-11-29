#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"

namespace seneca
{
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        public:
        //all deleted
        Workstation(Workstation&) = delete;
        Workstation operator = (Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator = (Workstation&&) = delete;
    };
}

#endif