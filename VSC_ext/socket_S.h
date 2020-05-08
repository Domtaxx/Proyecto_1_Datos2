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

class Socket_S{
private:
    int listening;
    sockaddr_in hint;
    void set_port(int port);
public:
    /**
     * @brief Socket_S constructor
     */
    Socket_S();

    int start(int _port = 54000);
    int mark_listening();
    int accept_calls();
};


#endif // SOCKET_H
