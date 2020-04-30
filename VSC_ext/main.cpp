#include <iostream>
#include "vsptr.hpp"

int main()
{
    VSPtr<std::string>* ptr = new VSPtr<std::string>();
    *ptr = "asda";
    return 0;
}
