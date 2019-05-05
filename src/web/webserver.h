#ifndef TT_WEB_SERVER_H
#define TT_WEB_SERVER_H

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "http.h"

namespace tt
{
    class WebServer
    {
    public:
        WebServer();

        void initialize(std::string ipAddress, unsigned short port);
        void start();
        void stop();
        void shutdown();

    private:
        int serverSocket;
        bool isStarted;

        struct sockaddr_in address;
        int maxConnections;
    };
}


#endif // TT_WEB_SERVER_H