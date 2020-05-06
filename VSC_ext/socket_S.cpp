#include "socket_S.h"
/**
* codigo fuente tomado de https://gist.github.com/codehoose/020c6213f481aee76ea9b096acaddfaf
* modificado por Brian Wagemans Alvarado
*/

Socket_S::Socket_S(){};
int Socket_S::Check_connection(){
    if (listening <= -1){
        std::cerr<<"can't create socket"<<std::endl;
        return -1;
    }else{
        std::cerr<<"socket is active"<<std::endl;
        return 0;
    }

};
int Socket_S::start(){
    sockaddr_in hint;
    hint.sin_family=AF_INET;
    hint.sin_port=htons(45000);
    inet_pton(AF_INET,"0.0.0.0", &hint.sin_addr);
    bind_and_check(hint);
    mark_listening();
    accept_calls();
    return 0;
};

int Socket_S::bind_and_check(sockaddr_in hint){
    if(bind(listening,(sockaddr*) &hint, sizeof(hint))== -1){
        std::cerr<<"can't bind to ip/port"<<std::endl;
        return -2;
    };return 1;
}
int Socket_S::mark_listening(){
    if(listen(listening,SOMAXCONN) == -1){
        std::cerr<<"can't listen"<<std::endl;
        return -3;
    }return 2;
};

int Socket_S::accept_calls(){
    client_size = sizeof(client);

    int client_socket = accept(listening,(sockaddr*) &client, &client_size);
    if(client_socket == -1){
        std::cerr<<"client problem"<<std::endl;
        return -4;
    }else{
        close(listening);
        memset(host, 0, NI_MAXHOST);
        memset(svc, 0, NI_MAXSERV);

        int result = getnameinfo((sockaddr*)&client,
                                 sizeof(client),host,NI_MAXHOST,
                                 svc, NI_MAXSERV,0);

        if(result){
            std::cout<<host<< " connected on "<< svc <<std::endl;
        }else{
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            std::cout<<host<< " connected on "<< ntohs(client.sin_port) <<std::endl;
        }
        char a_converted[4096];
        while (true){
                    recv(client_socket, (char*)a_converted, sizeof(a_converted), 0);

                    char char_array[sizeof(a_converted)];

                    strcpy(char_array, (char*)a_converted);
                    memset(a_converted, 0, sizeof(a_converted));
                    std::cout << "Client says: " << char_array << std::endl;
                    std::cout << std::endl;
        }close(client_socket);
        return 0;
    }
};
