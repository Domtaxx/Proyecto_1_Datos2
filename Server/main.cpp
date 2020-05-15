#include <iostream>
#include "vsptr.hpp"
#include "garbage.hpp"
#include <thread>
#include "pthread.h"
#include <unistd.h>
#include <fstream>
#include "socket_S.h"

int main(){
    Socket_S socket = Socket_S();

    VSPtr<int> ptr = VSPtr<int>::New();
    ptr = 5;
    VSPtr<int> ptr1 = VSPtr<int>::New();
    VSPtr<int> ptr2= VSPtr<int>::New();
    VSPtr<int> ptr3 = VSPtr<int>::New();
    VSPtr<int> ptr4= VSPtr<int>::New();
    ptr1=ptr;
    ptr3=ptr1;
    ptr=ptr1;
    ptr4=6;
    long* as;
    std::cout<<typeid(as).name()<<"\n";
    //socket.start();
    //socket.accept_calls();

}