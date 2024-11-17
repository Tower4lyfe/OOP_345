#ifndef SENECA_SET_H
#define SENECA_SET_H
#include "Collection.h" 


namespace seneca
{
    template <typename T, size_t capacity = 100>
    class set : public Collection<T, capacity>
    {
        bool add(const T &item)override;  
    };

    template <typename T, size_t capacity>
    inline bool set<T, capacity>::add(const T &item)
    {
        if(number == capacity)
        {
            return false;
        }

        for(size_t index = 0; index < number; index++)
        {
            if(m_items[index] == item) return false;
        }

        m_items[number++] = item;
        return true;
    }

    template<>
    inline bool set<double, capacity>::add(const double &item)
    {
        if(number == capacity)
        {
            return false;
        }

        for(size_t index = 0; index < number; index++)
        {
            if(std::fabs(m_items[index] - item)<=0.01) return false;
        }

        m_items[number++] = item;
        return true;        
    }

}

#endif