#ifndef TT_CLIENTSOCKET_H
#define TT_CLIENTSOCKET_H

#include <unistd.h>
#include <sys/socket.h>

class HttpRequest;

/**
 * @brief The ClientSocket class presents a TCP client of the webserver.
 */
class ClientSocket
{
public:
    ClientSocket(int server, struct ::sockaddr * address);

    bool accept();
    HttpRequest read() const;

    int socket() const;

    void close() const;

private:
    int _serverSocket;
    struct sockaddr * _serverAddress;
    int _clientSocket;
};

#endif // TT_CLIENTSOCKET_H