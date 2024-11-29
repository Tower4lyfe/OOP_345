/* - To Tsz, Lau,
- 125487248,
- ttlau3@myseneca.ca
- Nov 28th 2024 */
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

        static size_t m_widthField;
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