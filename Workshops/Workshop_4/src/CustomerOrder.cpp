#include "CustomerOrder.h"
#include <iomanip>


namespace seneca
{
    size_t m_widthField = 0;

    CustomerOrder::CustomerOrder()
    {
        m_name = "";
        m_product = "";
        m_cntItem = 0;
        m_lstItem = nullptr;
    }

    CustomerOrder::~CustomerOrder()
    {
        if(m_lstItem != nullptr)
        {
            for(size_t i = 0; i < m_cntItem; i++)
            {
                delete m_lstItem[i];
            }

            delete[] m_lstItem;
        }
    }

    CustomerOrder::CustomerOrder(const std::string & str)
    {
        Utilities util;
        size_t next_pos = 0;
        bool more = false;
        
        m_name = "";
        m_product = "";
        m_cntItem = 0;
        m_lstItem = nullptr;


        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);

        std::vector<std::string> items;
        while (more)
        {
            items.push_back(util.extractToken(str, next_pos, more));
        }

        m_cntItem = items.size();
        m_lstItem = new Item* [m_cntItem];

        for(size_t i = 0; i < m_cntItem; i++)
        {
            m_lstItem[i] = new Item(items[i]);
        }

        if(util.getFieldWidth() > m_widthField)
            m_widthField = util.getFieldWidth();
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& obj)noexcept
    {
        if(this == &obj)
        {
            return *this;
        }

        for(size_t i = 0; i < m_cntItem; i++)
        {
            delete m_lstItem[i];
        }
        delete[] m_lstItem;

        m_name = std::move(obj.m_name);
        m_product = std::move(obj.m_product);
        m_cntItem = obj.m_cntItem;
        m_lstItem = std::move(obj.m_lstItem);

        //sad funeral
        obj.m_lstItem = nullptr;
        obj.m_name = "";
        obj.m_product = "";

        return *this;
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& obj)noexcept
    {
        m_name = std::move(obj.m_name);
        m_product = std::move(obj.m_product);
        m_cntItem = obj.m_cntItem;
        m_lstItem = std::move(obj.m_lstItem);

        //sad funeral
        obj.m_lstItem = nullptr;
        obj.m_name = "";
        obj.m_product = "";
    }

    bool CustomerOrder::isOrderFilled() const
    {
        for(size_t i = 0; i < m_cntItem; i++)
        {
            if(!m_lstItem[i]->m_isFilled)
            {
                return false;
            }
        }

        return true;
    }
    
    bool CustomerOrder::isItemFilled(const std::string& itemName)const
    {
        for(size_t i = 0; i < m_cntItem; i ++)
        {
            if(m_lstItem[i]->m_itemName == itemName
            &&!m_lstItem[i]->m_isFilled)
            {
                return false;
            }
        }

        return true;
    }

    void CustomerOrder::fillItem(Station& Station, std::ostream& os)
    {
        for(size_t i = 0; i < m_cntItem; i++)
        {
            if(m_lstItem[i]->m_itemName == Station.getItemName())
                continue;

            if(Station.getQuantity() > 0)
            {
                m_lstItem[i]->m_serialnumber = Station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;
                os << "Filled " << m_name
                << ", " << m_product
                << "[" << Station.getItemName() << "]"
                << std::endl;
                Station.updateQuantity();
            }else
            {
                os << "Unable to fill "
                << m_name << ", " << m_product 
                << "[" << Station.getItemName() << "]"
                << std::endl;
            }
        }
    }

    void CustomerOrder::display(std::ostream& os)const
    {
        os << m_name << " - " << m_product << std::endl;
        for(size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << std::setw(6) << 
            m_lstItem[i]->m_serialnumber << "] - "
            << (m_lstItem[i]->m_isFilled?"FILLED":"TO BE FILLED")
            << std::endl;
        }
    }

}