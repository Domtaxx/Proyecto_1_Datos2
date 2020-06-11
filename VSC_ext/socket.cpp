#include "socket.hpp"

int Socket::vsptr_counter = 0;

Socket::Socket(int puerto, std::string ip){
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock == -1){
      //  return -1;
    }
    int port = puerto;
    string ipAdress = ip;

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET,ipAdress.c_str(), &hint.sin_addr);

    conectar(sock,hint);

}


int Socket::conectar(int sock, sockaddr_in hint){
    int connectResult = connect(sock, (sockaddr*)&hint, sizeof(sockaddr_in));
    if(connectResult == -1){
        connected = false;
        std::cout<<"no se conecto el socket"<<std::endl;
        return -1;
    }else{
        connected = true;
        std::cout<<"el socket esta activo"<<std::endl;
    }return 0;
}

string Socket::comunicar(string userInput){
    int sendResult = send(sock, userInput.c_str(), userInput.size()+1, 0);
    if(sendResult == -1){
        cout << "No se logró enviar al servidor\r\n";
    }
    char buf[4096];
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096,0);
    if(bytesReceived == 0){
        cerr << "Conexión perdida" << endl;
    }

    std::cout<<buf<<std::endl;
    return string(buf);
}

void Socket::comunicar_without_response(string userInput){
    int sendResult = send(sock, userInput.c_str(), userInput.size()+1, 0);
    if(sendResult == -1){
        cout << "No se logró enviar al servidor\r\n";
    }
}
std::string Socket::wait_msg(){
    char buf[4096];
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096,0);
    if(bytesReceived == 0){
        cerr << "Conexión perdida" << endl;
    }
    std::cout<<buf<<std::endl;
    return string(buf);
};

void Socket::closeSocket(){
    close(sock);
}
