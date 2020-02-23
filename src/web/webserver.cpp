#include "webserver.h"
#include "clientsocket.h"
#include "pageaddress.h"

#include <string.h>
#include <sstream>
#include <arpa/inet.h>


WebServer::WebServer():
    _serverSocket        (-1),
    _isStarted           (false),
    _maxConnections      (10),
    _persistor           ("timetracker.xml"),
    _timeTracker         (&_persistor),
    _actionController    (&_timeTracker),
    _pageGenerator       (&_timeTracker)
{
}

void WebServer::initialize(std::string ipAddress, unsigned short port)
{
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE); // TODO Error
    }


    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    _address.sin_port = htons( port );
    memset(_address.sin_zero, '\0', sizeof _address.sin_zero);

    int ret = bind(_serverSocket, (struct sockaddr *)&_address, sizeof(_address));
    if (ret < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE); // Todo Error
    }

    _pageGenerator.initialize();
    _actionController.initializeActions();
    _timeTracker.load();
}

void WebServer::start()
{

    if (listen(_serverSocket, _maxConnections) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE); // TODO Error
    }

    _isStarted = true;

    while(_isStarted)
    {
        ClientSocket client(_serverSocket, (struct sockaddr *)&_address);

        if (!client.accept())
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        HttpRequest request = client.read();
        // TODO errors

        HttpResponse response("Default Http Answer");
        if (request.getType() == Request_Get)
        {
            std::string path = request.getPath();
            response = processGetAction(path);
        }

        response.sendTo(client);
        client.close();

        if (request.getType() == Request_Get && request.getPath() == PageAddress::Quit)
        {
            _isStarted = false;
        }
    }
}

void WebServer::stop()
{
    _isStarted = false;
}

void WebServer::shutdown()
{
    ::close(_serverSocket);
}

HttpResponse WebServer::processGetAction(std::string path) const
{
    _actionController.execute(path);
    std::string nextPage = _pageGenerator.getPage(path);
    return HttpResponse(nextPage);
}
