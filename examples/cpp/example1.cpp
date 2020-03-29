#include <iostream>
#include "CPPLib/CPPLib.hpp"

int main(int argc, char const *argv[])
{
    std::string my_name = "Jeremy";
    std::cout << "My Name is " << my_name << std::endl;
    
    // Respond
    std::cout << CPPLib::Hello(my_name) << std::endl;

}
