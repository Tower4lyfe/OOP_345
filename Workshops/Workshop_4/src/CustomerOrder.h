#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H
#include "Station.h"

namespace seneca
{
    class CustomerOrder
    {
        struct Item
        {
            std::string m_itemName;
            size_t m_serialnumber{0};
            bool m_isFilled{false};

            Item(const std::string& src) : m_itemName(src){};
        };

        std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        Item** m_lstItem;
        static size_t m_widthField;

        public:
        CustomerOrder();
        ~CustomerOrder();
        CustomerOrder(const std::string &); //string
        //no copy
        CustomerOrder(const CustomerOrder&) = delete; 
        CustomerOrder operator =(const CustomerOrder&) = delete;
        CustomerOrder(CustomerOrder&&) noexcept;
        CustomerOrder operator =(CustomerOrder&&) noexcept;
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName)const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os)const;
    };

}


#endif