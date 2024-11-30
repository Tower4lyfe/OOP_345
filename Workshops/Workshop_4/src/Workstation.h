/* - To Tsz, Lau,
- 125487248,
- ttlau3@myseneca.ca
- Nov 29th 2024 */
#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace seneca
{
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation;
        
        public:
        //all deleted
        Workstation(Workstation&) = delete;
        Workstation operator = (Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator = (Workstation&&) = delete;

        //member functions:
        Workstation();
        ~Workstation();
        Workstation(const std::string& str);
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const;
        void display(std::ostream& os)const;
        Workstation& operator+=(CustomerOrder&& newOrder);
    };
}

#endif