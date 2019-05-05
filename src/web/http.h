#ifndef TT_HTTP_H
#define TT_HTTP_H

#include <string>
#include "clientsocket.h"

namespace tt
{
    class HttpResponse
    {
    public:
        HttpResponse(std::string content);

        void sendTo(const ClientSocket &client) const;

    private:
        std::string getSocketData() const;
        void makeHeader(std::string content);

    private:
        std::string header;
        std::string htmlContent;
    };

    enum RequestType {
        Request_Get,
        Request_Post,
        Request_Invalid
    };


    class HttpRequest
    {
    public:
        HttpRequest();

        void read(const ClientSocket &client);

        RequestType  getType() const;
        std::string getPath() const;

    private:
        void parseData(std::string data);

    private:
        RequestType requestType;

        std::string path;

    };
}

#endif // TT_HTTP_H