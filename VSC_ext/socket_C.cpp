#include "socket.hpp"

Socket::Socket(){
    sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock == -1){
      //  return -1;
    }
    int port = 54000;
    string ipAdress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET,ipAdress.c_str(), &hint.sin_addr);

    conectar(sock,hint);
   // return sock;

}


int Socket::conectar(int sock, sockaddr_in hint){
    int connectResult = connect(sock, (sockaddr*)&hint, sizeof(sockaddr_in));
    if(connectResult == -1){
        return -1;
    }
    return 0;
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


    return string(buf);
}


void Socket::closeSocket(int sock){
    close(sock);
}
