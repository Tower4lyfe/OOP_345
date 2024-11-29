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
        auto& currentOrder = m_orders.front();

        if(currentOrder.isItemFilled(this->getItemName())
        ||this->getQuantity() ==0)
        {
            if(m_pNextStation == nullptr)
            {
                if(currentOrder.isOrderFilled())
                {
                    g_completed.emplace_back(currentOrder);
                    m_orders.pop_front();
                    return true;
                }

                g_incomplete.emplace_back(currentOrder);
                m_orders.pop_front();
                return true;
            }
            m_pNextStation->m_orders.emplace_back(currentOrder);
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
        m_orders.emplace_back(newOrder);
    }

    void Workstation::display(std::ostream& os)const 
    {
        
        os << this->getItemName() 
    }

}