#ifndef TT_CLIENTSOCKET_H
#define TT_CLIENTSOCKET_H

#include <unistd.h>
#include <sys/socket.h>

namespace tt
{
    class HttpRequest;

    class ClientSocket
    {
    public:
        ClientSocket(int server, struct ::sockaddr * address);

        bool accept();
        HttpRequest read() const;

        int socket() const;

        void close() const;

    private:
        int serverSocket;
        struct sockaddr * serverAddress;
        int clientSocket;
    };
}

#endif // TT_CLIENTSOCKET_H