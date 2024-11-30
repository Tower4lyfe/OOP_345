#include "Workstation.h"
#include "CustomerOrder.h"
#include <deque>

namespace seneca 
{
    //Initializing Global Variables
    std::deque<seneca::CustomerOrder> g_pending;
    std::deque<seneca::CustomerOrder> g_completed;
    std::deque<seneca::CustomerOrder> g_incomplete;

    Workstation::Workstation():Station(""),m_pNextStation(nullptr){}
    Workstation::~Workstation(){}

    Workstation::Workstation(const std::string& str):Station(str){};

    void Workstation::fill(std::ostream&os)
    {
        if(!m_orders.empty())
        {
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder()
    {
        //Added for tester3
        if(m_orders.empty())
            return false;

        auto& currentOrder = m_orders.front();

        if(currentOrder.isItemFilled(this->getItemName())
        ||this->getQuantity() ==0)
        {
            if(m_pNextStation == nullptr)
            {
                if(currentOrder.isOrderFilled())
                {
                    g_completed.emplace_back(std::move(currentOrder));
                    m_orders.pop_front();
                    return true;
                }

                g_incomplete.emplace_back(std::move(currentOrder));
                m_orders.pop_front();
                return true;
            }
            m_pNextStation->m_orders.emplace_back(std::move(currentOrder));
            m_orders.pop_front();
            return true;
        }

        return false;
    }

    Workstation* Workstation::getNextStation() const
    {
        return m_pNextStation;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
    {
        m_orders.emplace_back(std::move(newOrder));
        return *this;
    }

    void Workstation::display(std::ostream& os)const 
    {
        if (m_pNextStation == nullptr)
            os << this->getItemName() << " --> End of Line\n";
        else
            os << this->getItemName() << " --> " << m_pNextStation->getItemName() << "\n";
    }

    void Workstation::setNextStation(Workstation* station)
    {
        this->m_pNextStation = station;
    }

}