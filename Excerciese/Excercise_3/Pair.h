#ifndef SENECA_PAIR_H
#define SENECA_PAIR_H
#include <iostream>

namespace seneca
{
    class Pair
    {
        std::string m_key{};
        std::string m_value{};

        public:
        const std::string& getKey() {return m_key;}
        const std::string& getValue(){return m_value;}
        Pair(const std::string& key, const std::string& value) : m_key{key}, m_value{value}{};

        bool operator==(const Pair& other)
        {
            return this->m_key==other.m_key;
        }
        
        friend std::ostream& operator<<(std::ostream& , Pair);

    };

    std::ostream& operator<<(std::ostream&os, Pair obj)
    {
        os << std::setw(20) << obj.m_key << ": " << obj.m_value;
        return os;
    }

}


#endif