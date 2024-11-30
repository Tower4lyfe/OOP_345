/* - To Tsz, Lau,
- 125487248,
- ttlau3@myseneca.ca
- Nov 28th 2024 */
#include "CustomerOrder.h"
#include <iomanip>
#include <vector>


namespace seneca
{
    size_t CustomerOrder::m_widthField = 0;

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

    CustomerOrder::CustomerOrder(const CustomerOrder &)
    {
        throw "ERROR: Cannot make copies.\n";
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
            //Debugging
            // std::cout << "\n=========Debug============\n";
            // std::cout << "m_lstItem[" << i << "]"
            // << "in isItemFilled is: " << m_lstItem[i]->m_itemName
            // <<std::endl;
            // std::cout << "====================\n";

            std::string itemInList = m_lstItem[i]->m_itemName;

            if(itemInList == itemName
            &&!m_lstItem[i]->m_isFilled)
            {
                // std::cout << "\nm_lstItem[" << i << "]: "
                // << itemInList 
                // << " is Not Filled. Will return false.\n"
                // << "Item Name is: " << itemName << std::endl;
 
                return false;
            }
        }

        return true;
    }

    void CustomerOrder::fillItem(Station& Station, std::ostream& os)
    {
        for(size_t i = 0; i < m_cntItem; i++)
        {
            //This Code is causing problem! But it shouldn't
            //THE MISSING SECOND CONDITION COST ME 4 HOURS...HOW? AM I STUPID?
            if(m_lstItem[i]->m_itemName != Station.getItemName()
            || m_lstItem[i]->m_isFilled)
                continue;

            
            if(Station.getQuantity() > 0)
            {
                m_lstItem[i]->m_serialnumber = Station.getNextSerialNumber();
                m_lstItem[i]->m_isFilled = true;
                os << "    Filled " << m_name
                << ", " << m_product
                << " [" << Station.getItemName() << "]"
                << std::endl;
                Station.updateQuantity();
                //I don't like breaking here...
                //What if user has more...
                break;
            }else
            {
                os << "Unable to fill "
                << m_name << ", " << m_product 
                << " [" << Station.getItemName() << "]"
                << std::endl;
            }
        }
        //Nothing in the order can be filled by this station
    }

    void CustomerOrder::display(std::ostream& os)const
    {
        os << m_name << " - " << m_product << std::endl;
        for(size_t i = 0; i < m_cntItem; i++)
        {
            os << "[" << std::right << std::setw(6) << std::setfill('0')<< 
            m_lstItem[i]->m_serialnumber << "] " 
            << std::left << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName
            << (m_lstItem[i]->m_isFilled?" - FILLED":" - TO BE FILLED")
            << std::endl;
        }
    }

}