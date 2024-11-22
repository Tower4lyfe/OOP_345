#include "toy.h"
#include <iomanip>

namespace seneca
{
    void Toy::update(int numItems)
    {
        numberOfItems = numItems;
    }

    Toy::Toy(const std::string& toy)
    {
        size_t index = toy.find(':');
        id = std::stoi(toy.substr(0,index++));
        size_t len = index;
        name = toy.substr(index, len = toy.find(':', index) - index);
        index += len+1;
        numberOfItems = std::stoi(toy.substr(index, len = toy.find(':', index) - index));
        index += len+1;
        price = std::stoi(toy.substr(index, len = toy.find('\0', index) - index));
    }

    std::ostream& operator << (std::ostream& os, const Toy& item) 
    {
        float subTotal = item.price * item.numberOfItems;
        float tax = subTotal * item.salesTax;
        float total = subTotal + tax;

        os.setf(std::ios::fixed);
        os.setf(std::ios::right);
        auto beforePrec = os.precision(2);
        auto beforeFill = os.fill();

        os << "Toy " << std::setfill('0') << std::setw(8) << item.id << ": "
        << std::setfill('.') << std::setw(24) << item.name <<' '
        << std::setfill(' ') << std::setw(2) << item.numberOfItems << " items @"
        << std::setfill(' ') << std::setw(6) << item.price << "/item subtotal:"
        << std::setfill(' ') << std::setw(7) << subTotal << " tax:"
        << std::setfill(' ') << std::setw(6) << tax << " total:"
        << std::setfill(' ') << std::setw(7) << total << '\n';

        os.precision(beforePrec);
        os.fill(beforeFill);
        os.unsetf(std::ios::fixed);
        os.unsetf(std::ios::right);
    }

    
}