#ifndef SOCKET_H
#define SOCKET_H
#include "Linked_List.hpp"
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

class Socket_S{
private:
    int listening = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in client;
    socklen_t client_size;
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    int bind_and_check(sockaddr_in hint);
    int mark_listening();
    int accept_calls();
    int Check_connection();
public:
    /**
     * @brief Socket_S constructor
     */
    Socket_S();
    /**
     * @brief starts the socket
     * @return
     */
    int start();

};


#endif // SOCKET_H
