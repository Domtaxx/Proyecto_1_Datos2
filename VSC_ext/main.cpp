#include <iostream>
#include "vsptr.hpp"
int main()
{
    VSPtr<std::string>* ptr = VSPtr<std::string>::New();
    *ptr = "asda";
    return 0;
}
