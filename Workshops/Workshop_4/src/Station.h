#ifndef SENECA_STATION_H
#define SENECA_STATION_H
#include "Utilities.h"

namespace seneca
{
    class Station
    {
        int m_id;
        std::string m_name;
        std::string m_description;
        unsigned int m_serialNumber;
        size_t m_quantity;

        static int m_widthField;
        static int id_generator;

        public:
        Station() = default;
        ~Station()= default;
        Station(const std::string&);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream&os, bool full)const;
    };
}


#endif