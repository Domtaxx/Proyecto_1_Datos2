#include "vsptr.hpp"
#include <unistd.h>
#include "garbage.hpp"
using namespace rapidjson;

bool is_not_finished = true;
void delete_t(){
    GarbageCollector* gc = GarbageCollector::getGarbageCollector();
    while(is_not_finished){
        gc->delete_pkgs();
        sleep(10);
    }
};
int main(){
    //std::thread p(delete_t);

    //Socket_C socket = Socket_C();


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
    socket.start();
    socket.accept_calls();

    GarbageCollector::getGarbageCollector()->delete_pkgs();*/;
    //Socket_C::remoteSocket = new Socket(std::stoi("54000"),"0.0.0.0");
    //std::string result = Socket_C::remoteSocket->comunicar("^Bruno Diaz,soyBatman123*");
    //sleep(5);
    VSPtr<int> ptr1 = VSPtr<int>::New();
    std::string msg = "{ \"tipo\" : \""+ptr1.ret_Type()+"\",\"localId\" : \""+ptr1.ret_Local_id()+"\"}";
    Document document;
    document.Parse<0>(msg.c_str());
    std::cout << document["tipo"].GetString();
    //is_not_finished = false;
    //p.join();
    return 0;
}

