#include <iostream>
#include "vsptr.hpp"
#include "garbage.hpp"
int main()
{
    GarbageCollector* rec = GarbageCollector::getGarbageCollector();
    for(int i =0; i<1025; i++){
        rec->add_Pkg_To_List(new specific_package<int>(i,10+i));
    }

    rec->add_ref(1023);
    rec->lower_ref(4);
    std::cout<<rec->get_Pkg_List().get_data_by_pos(4)->id<<std::endl;
    rec->delete_pkgs();
    std::cout<<rec->get_Pkg_List().get_data_by_pos(4)->id<<std::endl;
    return 0;
}
