#include "clientsocket.h"

#include "http.h"


#include <stdio.h>


using namespace tt;

ClientSocket::ClientSocket(int server, struct ::sockaddr *address):
    serverSocket        (server),
    serverAddress       (address),
    clientSocket        (-1)
{

}

bool ClientSocket::accept()
{
    socklen_t addrlen = sizeof(serverAddress);
    clientSocket = ::accept(serverSocket, (struct ::sockaddr *)&serverAddress, (socklen_t*)&addrlen);
    printf("\n+++++++ Waiting for new connection ++++++++\n\n");
    return clientSocket >= 0;
}

int ClientSocket::socket() const
{
    return clientSocket;
}

void ClientSocket::close() const
{
    ::close(clientSocket);
}

HttpRequest ClientSocket::read() const
{
    HttpRequest request;
    request.read(*this);
    return request;
}
