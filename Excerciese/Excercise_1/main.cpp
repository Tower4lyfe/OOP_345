#include <iostream>

int main(int argc, char** argv)
{
    for(int count = 0; count < argc; ++count)
    {
        std::cout << count+1 << ": ";
        std::cout << argv[count] << std::endl;
    }

    return 0;
}