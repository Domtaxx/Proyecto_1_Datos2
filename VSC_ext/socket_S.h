#ifndef SOCKET_H
#define SOCKET_H
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "garbage.hpp"

class Socket_S{
private:
    int listening;
    sockaddr_in hint;
    void set_port(int port);
    sockaddr_in client;
    socklen_t client_Size = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];

public:
    /**
     * @brief Socket_S constructor
     */
    Socket_S();
    int start(int _port = 54000);
    int mark_listening();
    int accept_calls(package pack);
};


#endif // SOCKET_H
