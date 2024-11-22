#ifndef SENECA_SET_H
#define SENECA_SET_H
#include "Collection.h" 


namespace seneca
{
    constexpr size_t capacity = 100;
    template <typename T>
    class Set : public Collection<T, capacity>
    {
        bool add(const T &item)override;  
    };

    template <typename T>
    inline bool Set<T>::add(const T &item)
    {

        for(size_t index = 0; index < this->size(); index++)
        {
            if(this->operator[](index) == item) return false;
        }

        return Collection<T, capacity>::add(item);
    }

    template<>
    inline bool Set<double>::add(const double &item)
    {

        for(size_t index = 0; index < this->size(); index++)
        {
            if(std::fabs(this->operator[](index) - item)<=0.01) return false;
        }

        return Collection<double, capacity>::add(item);
    }

}

#endif