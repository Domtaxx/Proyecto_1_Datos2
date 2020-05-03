#include <iostream>
#include "vsptr.hpp"
#include "garbage.hpp"
#include <thread>
#include "pthread.h"
#include <unistd.h>
bool* flag = new bool(true);
void algo(){
    while(*flag){
        GarbageCollector::getGarbageCollector()->delete_pkgs();
        std::cout<<"FIUM"<<std::endl;
        sleep(10);
    }
    return;
};

int main(){
    GarbageCollector* rec = GarbageCollector::getGarbageCollector();
    for(int i =0; i<100001; i++){
        rec->add_Pkg_To_List(new specific_package<int>(i,10+i));
    }
    rec->add_ref(3);
    std::thread prueba(algo);
    
    std::cout<<rec->get_Pkg_List().get_data_by_pos(4)->id<<std::endl;
    for(int i =0; i<1000101; i++){
        rec->lower_ref(i);
    }
    std::cin.get();
    *flag = false;
    prueba.join();
    delete flag;
}
