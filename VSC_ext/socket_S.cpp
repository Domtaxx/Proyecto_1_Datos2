#include "socket_S.h"

Socket_S::Socket_S(){};
void Socket_S::set_port(int port){
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port); //htons = host to network short (Little Indian o Big Indian)
    inet_pton(AF_INET, "0.0.0.0",&hint.sin_addr); //ip del server
}


int Socket_S::start(int _port){
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

int Socket_S::mark_listening(){
    if(listen(listening, SOMAXCONN)== -1){
        std::cerr<<"can't listen to clients \n";
        return -3;
    }return 1;
}

int Socket_S::accept_calls(package pack){
    int clientSocket = accept(listening, (sockaddr*)&client, &client_Size);// aqui
    std::cout<<"me acepto \n";
    if(clientSocket == -1){
        std::cerr<<"error connecting to client \n";
        return -4;
    }close(listening);
    memset(host, 0, NI_MAXHOST);
    memset(svc, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, svc, NI_MAXSERV, 0);
    if(result){
        std::cout<<" host coneccted on "<< svc<< std::endl;
    }else{
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout<< host << " connected on "<< ntohs(client.sin_port)<< std::endl;
    }std::cout<<"me sali \n";

    std::string pito = "";
    pito+=pack.ret_Type()+",";
    pito+=pack.ret_Val()+",";
    pito+=std::to_string(pack.ref_counter)+",";
    pito+=std::to_string(pack.id);
    send(clientSocket, &pito, sizeof(pito),0);
    return 0;
};

