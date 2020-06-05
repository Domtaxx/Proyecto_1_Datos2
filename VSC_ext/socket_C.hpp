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
    bool start_main_thread;
public:
    /**
     * @brief Socket_S constructor
     */
    Socket_C();
    ~Socket_C();
    static Socket* remoteSocket;
    static Socket* JS_socket;
    int start(int _port = 51000);
    bool try_connection(int port, std::string ip, std::string username, std::string password);
};


#endif // SOCKET_H
