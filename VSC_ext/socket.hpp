#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;
/**
 * @brief The Socket class
 * Clase que controla la creación de sockets, así como su comunicación con el servidor
 * Código basado en https://gist.github.com/codehoose/d7dea7010d041d52fb0f59cbe3826036
 */
class Socket{
public:
    bool connected;
    /**
     * Constructor del socket, encargado de iniciarlizar el socket y conectarlo al servidor
    */
    Socket(int puerto, std::string ip);
    /**
     * @brief sock
     * Variable que almacena el socket creado en el constructor
     */
    static int vsptr_counter;
    int sock;
    /**
     * @brief conectar
     * @param sock
     * @param hint
     * @return
     * Método encargado de conectar el socket con el servidor, llamado desde el constructor
     */
    int conectar(int sock, sockaddr_in hint);
    /**
     * @brief comunicar
     * @param userInput
     * @return
     * Método encargado de enviar mensajes y recibirlos, los convierte en una variable de tipo std::string
     */
    void comunicar_without_response(string userInput);
    /**
     * @brief comunicar con el server sin esperar respuesta
     * @param userInput
     * Método encargado de enviar mensajes.
     */
    string comunicar(string userInput);
    /**
     * @brief closeSocket
     * @param socket
     * Método que finaliza la conexión del socket con el servidor.
     */

    void closeSocket();
    /**
     * Método que permite el singleton al ser el único capaz de acceder al constructor
     */
    static Socket getSocket();
    std::string wait_msg();
private:

};

#endif // SOCKET_HPP
