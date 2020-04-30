#include <iostream>
#include "vsptr.hpp"
int main()
{
    VSPtr<std::string> ptr = VSPtr<std::string>::New();
    ptr = "pto";

    std::cout<<&ptr<<std::endl;
    return 0;
}
