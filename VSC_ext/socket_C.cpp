#include "socket_C.hpp"
Socket* Socket_C::remoteSocket = NULL;
Socket* Socket_C::JS_socket = NULL;
Socket_C::Socket_C(){};

int Socket_C::start(int _port){
    // se crea el puerto del server
    JS_socket = new Socket(_port, "0.0.0.0");

    std::string infoData = JS_socket->wait_msg();
    if (infoData.substr(0,3)== "true"){
        std::string datos[5];
        for(int i=0; i < 5; i++){
            std::string token = infoData.substr(0,infoData.find(","));
            datos[i] = token;
            infoData.erase(0,infoData.find(",")+1);
            Socket_C::remoteSocket = new Socket(std::stoi(datos[4]),datos[3]);
            std::string result = Socket_C::remoteSocket->comunicar("^"+datos[1]+","+datos[2]+"*");
            if(result == "error"){
                Socket_C::remoteSocket->closeSocket();
                JS_socket->comunicar_without_response("error");
            }if(result == "success"){
                JS_socket->comunicar_without_response("success");
                GarbageCollector::server_on = true;
            }
        }
};

int Socket_C::mark_listening(){
    if(listen(listening, SOMAXCONN)== -1){
        std::cerr<<"can't listen to clients \n";
        return -3;
    }return accept_calls();
}

int Socket_C::accept_calls(){
    //std::thread GC(start_garbage);
    std::string msg = "";
    std::string VSptr = "";

    int clientSocket = accept(listening, (sockaddr*)&client, &client_Size);// aqui
    std::cout<<"me acepto \n";
    if(clientSocket == -1){
        std::cerr<<"error connecting to client \n";
        return -4;
    }

    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);
    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);
    if(result){
        std::cout<<" host coneccted on "<< svc<< std::endl;
    }else{
          inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
          std::cout<< host << " connected on "<< ntohs(client.sin_port)<< std::endl;
    };
    char buf[4096];
    while(!end){
        memset(buf, 0, 4096);
        int bytesReceived = recv(clientSocket, buf, 4096,0);
        if(bytesReceived == 0){
            std::cerr << "Conexión perdida" << std::endl;
            return -5;
        }
        std::string infoData = string(buf);
        if(buf[0]=='$' && buf[1]=='$'){
            for(int i = 0; i < GarbageCollector::getGarbageCollector()->get_Pkg_List().get_object_counter();i++){
                package* pack = GarbageCollector::getGarbageCollector()->get_Pkg_List().get_data_by_pos(i);
                std::string val = pack->ret_Val().c_str();
                std::string tipo = pack->ret_Type().c_str();
                std::string addr = pack->ret_Mem_Addr().c_str();
                std::string id = std::to_string(pack->id);
                std::string ref = std::to_string(pack->ref_counter);
                msg += id+","+ tipo+","+val+","+addr+","+ref;
                if((i+1) == GarbageCollector::getGarbageCollector()->get_Pkg_List().get_object_counter()){
                    msg+= "&";
                }else{
                    msg+= ".";
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
                    msg+= ".";
                };
            };
            send(clientSocket, msg.data(), msg.size() ,0);
        }

        else if (infoData.substr(0,3)== "true"){
            std::string datos[5];
            for(int i=0; i < 5; i++){
                std::string token = infoData.substr(0,infoData.find(","));
                datos[i] = token;
                infoData.erase(0,infoData.find(",")+1);
            }

            Socket_C::remoteSocket = new Socket(std::stoi(datos[4]),datos[3]);
            std::string result = Socket_C::remoteSocket->comunicar("^"+datos[1]+","+datos[2]+"*");
            if(result == "error"){
                Socket_C::remoteSocket->closeSocket();
                std::string msg = "error";
                send(clientSocket,msg.data(),msg.size(),0);
            }if(result == "success"){
                std::string msg = "success";
                send(clientSocket,msg.data(),msg.size(),0);
                GarbageCollector::server_on = true;
            }
        }
    };

    std::cout<<"finished  \n";
    return 0;
};
void Socket_C::comunicar_without_response(string userInput){
    int sendResult = send(listening, userInput.c_str(), userInput.size()+1, 0);
    if(sendResult == -1){
        cout << "No se logró enviar al servidor\r\n";
    }
}
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
                msg+= ".";
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
            msg+= ".";
        };
    };
    return msg;
}
