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
        size_t m_numberOfItems;

        static int m_widthField;
        static int id_generator;

        public:
        Station() = default;
        ~Station()= default;
        Station(const std::string&);

    };
}


#endif