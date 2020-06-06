#include "vsptr.hpp"
 bool is_not_finished = true;
    void delete_t(){
        GarbageCollector* gc = GarbageCollector::getGarbageCollector();
        gc->thread_function(&is_not_finished);
    };
int main(){
    std::thread p(delete_t);
    Socket_C socket = Socket_C();
    socket.start();
    //code here
    //code end
    is_not_finished = false;
    p.join();
    return 0;
};
