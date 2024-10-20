#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

namespace seneca
{
    template <typename T, size_t capacity>
    class Collection
    {
        T m_items[capacity]{}; // static allocated array of obj
        size_t number{}; // number of items 
        static T default_value{}; // default value 

        public:
            size_t size() {return number;}
            void display()const;
            virtual bool add(const T& item);
            
    };

    template <typename T, size_t capacity>
    inline void Collection<T, capacity>::display() const
    {
    }
}

#endif