#ifndef TT_WEB_SERVER_H
#define TT_WEB_SERVER_H

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

#include "http.h"
#include "pagegenerator.h"
#include "actioncontroller.h"
#include "core/timetracker.h"

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
        HttpResponse processGetAction(std::string path) const;

    private:
        int _serverSocket;
        bool _isStarted;

        struct sockaddr_in _address;
        int _maxConnections;
        PageGenerator _pageGenerator;
        ActionController _actionController;

        FilePersistor _persistor;
        TimeTracker _timeTracker;
    };
}


#endif // TT_WEB_SERVER_H