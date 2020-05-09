#include <iostream>
#include "vsptr.hpp"
#include "garbage.hpp"
#include <thread>
#include "pthread.h"
#include <unistd.h>
#include "include/rapidjson/document.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/ostreamwrapper.h"
#include <fstream>
#include "socket_S.h"

using namespace rapidjson;
using namespace std;
bool* flag = new bool(true);
void loopGC(){
    while(flag){
        GarbageCollector::getGarbageCollector()->delete_pkgs();
        sleep(10);
    }
    return;
};
int main(){
    Socket_S socket = Socket_S();
    //std::thread GC(loopGC);

    //std::string  p = GarbageCollector::getGarbageCollector()->get_Pkg_List().get_data_by_pos(0)->ret_Val();
    //std::string  R = GarbageCollector::getGarbageCollector()->get_Pkg_List().get_data_by_pos(0)->ret_Type();

    //std::cout<<p<<std::endl;
    //std::cout<<typeid(4).name()<<std::endl;
    /*
    ifstream ifs("JSONFiles/prueba.json");
    IStreamWrapper isw (ifs);
    Document root;
    root.ParseStream(isw);

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    root.Accept(writer);

    std::string jsonStr(buffer.GetString());
        if(jsonStr == "null"){
            std::cout << "is null..." << std::endl; //<--always here!
        }else{
            std::cout << jsonStr.c_str() << std::endl;
            root["ip"] = "pito";
            ofstream ofs("JSONFiles/prueba.json");
            OStreamWrapper osw(ofs);
            Writer<OStreamWrapper> writer2(osw);
            root.Accept(writer2);
        }
    std::cout<<(root["angle z"].GetInt())<<::std::endl;
    */


    socket.start();
    specific_package<int> alv = specific_package<int>();
    alv.data = 5;
    alv.id = 1;
    socket.accept_calls(alv);
    *flag = false;
    delete flag;
    //GC.join();


    return 0;
}
