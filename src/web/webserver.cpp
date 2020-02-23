#include "webserver.h"
#include "clientsocket.h"
#include "pageaddress.h"

#include <string.h>
#include <sstream>
#include <arpa/inet.h>

using namespace tt;

WebServer::WebServer():
    serverSocket        (-1),
    isStarted           (false),
    maxConnections      (10),
    persistor           ("timetracker.xml"),
    timeTracker         (&persistor),
    actionController    (&timeTracker),
    pageGenerator       (&timeTracker)
{
}

void WebServer::initialize(std::string ipAddress, unsigned short port)
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE); // TODO Error
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    address.sin_port = htons( port );
    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    int ret = bind(serverSocket, (struct sockaddr *)&address, sizeof(address));
    if (ret < 0)
    {
        perror("In bind");
        exit(EXIT_FAILURE); // Todo Error
    }

    pageGenerator.initialize();
    actionController.initializeActions();
}

void WebServer::start()
{

    if (listen(serverSocket, maxConnections) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE); // TODO Error
    }

    isStarted = true;

    while(isStarted)
    {
        ClientSocket client(serverSocket, (struct sockaddr *)&address);

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
            isStarted = false;
        }
    }
}

void WebServer::stop()
{
    isStarted = false;
}

void WebServer::shutdown()
{
    ::close(serverSocket);
}

HttpResponse WebServer::processGetAction(std::string path) const
{
    actionController.execute(path);
    std::string nextPage = pageGenerator.getPage(path);
    return HttpResponse(nextPage);
}
