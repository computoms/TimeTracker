#include "clientsocket.h"
#include "http.h"

#include <stdio.h>

ClientSocket::ClientSocket(int server, struct ::sockaddr *address):
    _serverSocket        (server),
    _serverAddress       (address),
    _clientSocket        (-1)
{

}

bool ClientSocket::accept()
{
    socklen_t addrlen = sizeof(_serverAddress);
    _clientSocket = ::accept(_serverSocket, (struct ::sockaddr *)_serverAddress, (socklen_t*)&addrlen);
    printf("\n+++++++ Waiting for new connection ++++++++\n\n");
    return _clientSocket >= 0;
}

int ClientSocket::socket() const
{
    return _clientSocket;
}

void ClientSocket::close() const
{
    ::close(_clientSocket);
}

HttpRequest ClientSocket::read() const
{
    HttpRequest request;
    request.read(*this);
    return request;
}
