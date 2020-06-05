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
    VSPtr<int> int1 = VSPtr<int>::New();
    int1 = 9;
    VSPtr<double> num = VSPtr<double>::New();
    num=(&int1+.006);
    std::cout<<&num<<std::endl;
    sleep(10);
    //code end
    is_not_finished = false;
    p.join();
    return 0;
};
