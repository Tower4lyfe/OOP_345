#include <iostream>
#include <thread>
#include <future>


thread_local int value = 0; 

void changeValue(std::promise<int> &value)
{
    std::cout << "Value before it is changed: " << value.get() << std::endl;
    value.set_value(rand());
    std::cout << "Value after it is changed: " << 
}


int main(int, char**)
{
    std::cout<< "Main Thread Starting...\n" << std::this_thread::get_id();

    return 0; 
}