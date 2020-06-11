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
    
public:
    /**
     * @brief Socket_C constructor
     */
    Socket_C();
    /**
     * @brief Destroy the Socket_C object
     */
    ~Socket_C();
    /**
     * @brief socket that connects to the server
     */
    static Socket* remoteSocket;
    /**
     * @brief sockets that connects to the JS_client
     */
    static Socket* JS_socket;
    /**
     * @brief starts the proxy
     * @param _port port to connect to
     * @return int indicator if it connected
     */
    int start(int _port = 51000);
    /**
     * @brief trys the connection, and returns a boolean depending
     * 
     * @param port to connect to
     * @param ip to connect to
     * @param username username inside the server database
     * @param password password inside the server database
     * @return true if it connected
     * @return false if it did not connect
     */
    bool try_connection(int port, std::string ip, std::string username, std::string password);
    /**
     * @brief starts the main thread
     */
    bool start_main_thread;
};


#endif // SOCKET_H
