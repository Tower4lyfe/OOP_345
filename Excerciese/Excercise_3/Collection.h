#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H
#include "Pair.h"

namespace seneca
{
    template <typename T, size_t capacity>
    class Collection
    {
        T m_items[capacity]{}; // static allocated array of obj
        size_t number{}; // number of items 
        static T default_value; // default value 

        public:
            size_t size() {return number;}
            void display()const;
            virtual bool add(const T& item);
            T operator[](size_t index)const;

            virtual ~Collection() = default; //why
    };

    template<typename T, size_t capacity>
    inline T Collection<T, capacity>::default_value{};

    //needs to be inline to prevent multiple definition
    template<>
    inline Pair Collection<Pair, 100>::default_value{"No Key", "No Value"}; 


    template <typename T, size_t capacity>
    inline void Collection<T, capacity>::display() const
    {
        std::cout << "Diplaying:\n";
        for(size_t index = 0; index < number; index++)
        {
            std::cout << m_items[index] << std::endl;
        }
    }

    template <typename T, size_t capacity>
    inline bool Collection<T, capacity>::add(const T &item)
    {
        if(number == capacity)
        {
            return false;
        }

        m_items[number++] = item;
        return true;
    }

    template <typename T, size_t capacity>
    inline T Collection<T, capacity>::operator[](size_t index)const
    {
        if(index >= number) return default_value;
        return m_items[index];
    }
}

#endif