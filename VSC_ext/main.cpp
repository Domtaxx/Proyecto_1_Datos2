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


using namespace rapidjson;
using namespace std;;


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
    /*GarbageCollector* rec = GarbageCollector::getGarbageCollector();
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
    delete flag; */

    ifstream ifs("JSONFiles/prueba.json");
    IStreamWrapper isw (ifs);
    Document root;
    root.ParseStream(isw);

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    root.Accept(writer);

    std::string jsonStr(buffer.GetString());
        /*if(jsonStr == "null")
            std::cout << "is null..." << std::endl; //<--always here!
        else
        {
            std::cout << jsonStr.c_str() << std::endl;

            root["ip"] = "123456789";

            ofstream ofs("JSONFiles/prueba.json");
            OStreamWrapper osw(ofs);
            Writer<OStreamWrapper> writer2(osw);
            root.Accept(writer2);
        }*/
    printf(root["ip"].GetString());


}
