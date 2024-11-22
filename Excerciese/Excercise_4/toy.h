#ifndef SENECA_TOY_H
#define SENECA_TOY_H
#include <iostream>

namespace seneca
{
    class Toy
    {
        unsigned int id;
        std::string name;
        size_t numberOfItems;
        float price;
        float salesTax = 0.13;
        
        public:
        Toy() = default;
        void update (int numItems);
        Toy(const std::string& toy);
        friend std::ostream& operator << (std::ostream&,const Toy&);
    };


}



#endif