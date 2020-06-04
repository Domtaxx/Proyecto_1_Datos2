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
#include "thread"
#include "socket.hpp"

class Socket_C{
private:
    bool end = false;
    int listening;
    sockaddr_in hint;
    void set_port(int port);
    sockaddr_in client;
    socklen_t client_Size = sizeof(client);
    char host[NI_MAXHOST];
    char svc[NI_MAXSERV];
    static void start_garbage();

public:
    /**
     * @brief Socket_S constructor
     */
    Socket_C();
    static Socket* remoteSocket;
    static Socket* JS_socket;
    int start(int _port = 51000);
    int mark_listening();
    int accept_calls();
    void comunicar_without_response(string userInput);
};


#endif // SOCKET_H
