#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include "FoodOrder.h"

double g_taxrate = 0;
double g_dailydiscount = 0;

namespace seneca
{

    seneca::FoodOrder::~FoodOrder()
    {
        delete [] food_description;
    }


    seneca::FoodOrder::FoodOrder(const FoodOrder &item)
    {
        *this = item;
    }

    FoodOrder &FoodOrder::operator=(const FoodOrder &item)
    {
        if(this!= &item)
        {
            delete[] food_description;
            food_description = nullptr;

            //shallow copy
            strcpy(customer_name, item.customer_name);
            price = item.price;
            special = item.special;

            //deep copy
            if(item.food_description)
            {
                food_description = new char[strlen(item.food_description)+1];
                strcpy(food_description, item.food_description);
            }

        }

        return *this;
    }

    void seneca::FoodOrder::read(std::istream &is_item)
    {
        if(is_item)
        {
            is_item.getline(customer_name, 10, ',');

            if(food_description) 
                delete[] food_description;
            
            std::string buffer;
            getline(is_item, buffer, ',');

            food_description = new char[buffer.length()+1];
            strcpy(food_description, buffer.c_str());

            is_item >> price;
            char temp {'N'};

            is_item.ignore();
            is_item >> temp;
            temp == 'N'? special = false : special = true;
        }

    }

    void seneca::FoodOrder::display() const
    {
        static size_t counter = 0;
        std::cout << std::left << std::setw(2) << ++counter << ". ";

        if(customer_name[0])
        {
            double priceTaxed = price + (price * g_taxrate);
            std::cout << std::setw(10) << customer_name << "|"
            << std::setw(25) << food_description << "|" << std::fixed
            << std::setw(12) << std::setprecision(2) << priceTaxed << "|";

            if(special)
            std::cout << std::right << std::setprecision(2) <<
            std::setw(13) << priceTaxed -g_dailydiscount;
        }
        else 
            std::cout << "No Order";
            
        std::cout << std::endl;
    }

}