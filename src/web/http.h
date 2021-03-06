#ifndef TT_HTTP_H
#define TT_HTTP_H

#include <string>
#include "clientsocket.h"

/**
 * @brief The HttpResponse class represents an HTTP response (TCP).
 */
class HttpResponse
{
public:
    HttpResponse(std::string content);

    void sendTo(const ClientSocket &client) const;

private:
    std::string getSocketData() const;
    void makeHeader(std::string content);

private:
    std::string _header;
    std::string _htmlContent;
};

enum RequestType {
    Request_Get,
    Request_Post,
    Request_Invalid
};

/**
 * @brief The HttpRequest class represents an HTTP request (TCP).
 */
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
    RequestType _requestType;

    std::string _path;

};


#endif // TT_HTTP_H