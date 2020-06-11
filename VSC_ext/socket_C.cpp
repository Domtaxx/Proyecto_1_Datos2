#include "socket_C.hpp"
Socket* Socket_C::remoteSocket = NULL;
Socket* Socket_C::JS_socket = NULL;
Socket_C::Socket_C(){};

int Socket_C::start(int _port){
    // se crea el puerto del server
    bool conncection = false;
    std::string stop = "stop";
    std::string _true = "true";
    JS_socket = new Socket(_port, "0.0.0.0");
    while(!conncection){
        if(!JS_socket->connected){
            if(JS_socket!=nullptr){
                JS_socket->closeSocket();
                delete JS_socket;
            }JS_socket = new Socket(_port, "0.0.0.0");
        }else{
            std::string infoData = JS_socket->wait_msg();
            std::string user_true = infoData.substr(0,4);
            if (user_true == _true){
                std::cout<<"aiuda\n";
                std::string datos[5];
                for(int i=0; i < 5; i++){
                    std::string token = infoData.substr(0,infoData.find(","));
                    datos[i] = token;
                    infoData.erase(0,infoData.find(",")+1);
                }
                conncection = try_connection(std::stoi(datos[4]),datos[3],datos[1],datos[2]);
            }if(infoData == stop){
               std::cout<<"Garbage Local :3"<<std::endl;
               GarbageCollector::server_on = false;
               break;
            }
        }
    }
    std::string msg;
    while(msg!="start" && conncection){
        msg = JS_socket->wait_msg();
        std::cout<<"ejecuta el resto del codigo del usuario"<<std::endl;
    }start_main_thread = true;
    return 1;
};
bool Socket_C::try_connection(int port, std::string ip, std::string username, std::string password){
    try{
        remoteSocket = new Socket(port, ip);
        std::string result = remoteSocket->comunicar("^"+username+","+password+"*");
        if(result == "error"){
            Socket_C::remoteSocket->closeSocket();
            JS_socket->comunicar_without_response("error");
            std::cout<<"err de conexion"<<std::endl;
            return false;
        }else if(result == "success"){
            JS_socket->comunicar_without_response("success");
            GarbageCollector::server_on = true;
            std::cout<<"se conecto al Server :3"<<std::endl;
            return true;
        }else{
            return false;
        }
    }catch(...){
        if(remoteSocket!=nullptr){
            delete remoteSocket;
        }return false;
    }
};

std::string GarbageCollector::GC_data(){
    std::string msg;
    for(int i = 0; i < GarbageCollector::getGarbageCollector()->get_Pkg_List().get_object_counter();i++){
            package* pack = GarbageCollector::getGarbageCollector()->get_Pkg_List().get_data_by_pos(i);
            std::string val = pack->ret_Val().c_str();
            std::string tipo = pack->ret_Type().c_str();
            std::string addr = pack->ret_Mem_Addr().c_str();
            std::string id = std::to_string(pack->id);
            std::string ref = std::to_string(pack->ref_counter);
            msg += id+","+tipo+","+val+","+addr+","+ref;
            if((i+1) == GarbageCollector::getGarbageCollector()->get_Pkg_List().get_object_counter()){
                msg+= "&";
            }else{
                msg+= "*";
            };
    };
    for(int i = 0; i < GarbageCollector::getGarbageCollector()->get_Vsptr_List().get_object_counter();i++){
        vsptrNT* ptr = GarbageCollector::getGarbageCollector()->get_Vsptr_List().get_data_by_pos(i);
        std::string id = ptr->ret_Id().c_str();
        std::string type = ptr->ret_Type().c_str();
        std::string value = ptr->ret_Val().c_str();
        msg += id +","+ type + ","+ value;
        if((i+1) == GarbageCollector::getGarbageCollector()->get_Vsptr_List().get_object_counter()){
            msg+= ";";
        }else{
            msg+= "*";
        };
    };
    return msg;
}
Socket_C::~Socket_C(){
    if(remoteSocket!=nullptr){
        delete remoteSocket;
    }
    if(JS_socket!=nullptr){
        delete JS_socket;
    }
}
