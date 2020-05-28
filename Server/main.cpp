#include <iostream>
#include "vsptr.hpp"
#include "garbage.hpp"
#include <thread>
#include "pthread.h"
#include <unistd.h>
#include <fstream>
#include "socket_S.h"
#include "md5.h"
int main(){
    GarbageCollector* gc = GarbageCollector::getGarbageCollector();
    std::cout << "md5 of 'grape': " << md5("grape") << std::endl;

    //Socket_S socket = Socket_S();
    //socket.start();
}