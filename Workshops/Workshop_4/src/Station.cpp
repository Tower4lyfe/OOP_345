#include "Station.h"
#include <string>


namespace seneca
{
    int Station::m_widthField = 0;
    int Station::id_generator = 0;

    Station::Station(const std::string& str)
    {
        Utilities util;
        size_t next_pos = 0;
        bool more = false;
        m_id = id_generator++;

        m_name = util.extractToken(str, next_pos, more);
        m_serialNumber = std::stoi(util.extractToken(str, next_pos, more));
        m_quantity = std::stoi(util.extractToken(str, next_pos, more));

        if(util.getFieldWidth() > m_widthField)
        {
            m_widthField = util.getFieldWidth();
        }
        m_description = util.extractToken(str, next_pos, more);
    }

    const std::string& Station::getItemName()const
    {
        return m_name;
    }

    size_t Station::getNextSerialNumber()
    {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const
    {
        return m_quantity;
    }

    void Station::updateQuantity()
    {
        if(m_quantity>0)
        {
            m_quantity--;
        }
    }

    void Station::display(std::ostream& os, bool full)const
    {
        
    }
}