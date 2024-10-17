#ifndef FOODORDER_H
#define FOODORDER_H
#include <iostream>

extern double g_taxrate;
extern double g_dailydiscount;

namespace seneca
{
	class FoodOrder 
	{
		char customer_name[10]{};
		char* food_description{};
		double price{};
		bool special{};

	public:
		FoodOrder(){};//default constructor
		~FoodOrder();//destructor?
		FoodOrder(const FoodOrder& item);//Copy Constructor?
		FoodOrder& operator=(const FoodOrder& item);
		void read(std::istream &is_item);
		void display() const;

	};
}

#endif