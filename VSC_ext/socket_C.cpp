#include "socket_C.h"

Socket_C::Socket_C(){};
void Socket_C::set_port(int port){
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port); //htons = host to network short (Little Indian o Big Indian)
    inet_pton(AF_INET, "0.0.0.0",&hint.sin_addr); //ip del server
}
void Socket_C::start_garbage(){
    GarbageCollector* rec = GarbageCollector::getGarbageCollector();
    while(!rec->server_on){
        rec->delete_pkgs();
        sleep(10);
    };
};

int Socket_C::start(int _port){

    listening = socket(AF_INET, SOCK_STREAM, 0);
    if(listening == -1){
        std::cerr<<"could not creat socket \n";
        return -1;
    }
    // se crea el puerto del server
    set_port(_port);
    if(bind(listening, (sockaddr*)&hint, sizeof(hint))==-1){
        std::cerr<<"can't bind to port \n";
        return -2;
    }
    return mark_listening();
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
        }else if (buf[0]=='@' && buf[1]=='@' && buf[2]=='@'){
            GarbageCollector::server_on = true;
            Socket_C::remoteSocket = new Socket(54000,"127.0.0.1");
        }
    };

    std::cout<<"finished  \n";
    return 0;
};
