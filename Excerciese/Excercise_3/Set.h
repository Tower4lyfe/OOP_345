#ifndef SENECA_SET_H
#define SENECA_SET_H
#include "Collection.h" 


namespace seneca
{
    template <typename T, size_t capacity = 100>
    class set : public Collection<T, capacity>
    {
        
    };

}



#endif