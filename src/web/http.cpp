#include "http.h"

#include <sstream>
#include <unistd.h>

using namespace tt;

HttpResponse::HttpResponse(std::string content)
{
    makeHeader(content);
    htmlContent = content;
}

void HttpResponse::makeHeader(std::string content)
{
    std::stringstream ss;
    ss << "HTTP/1.1 200 OK" << "\r\n";
    ss << "Date: Sun, 05 May 2019 13:28:27 GMT" << "\r\n"; // TODO Write date
    ss << "Server: computoms" << "\r\n";
    ss << "Content-Type: text/html;charset=UTF-8" << "\r\n";
    ss << "Content-Length: " << content.size() << "\r\n";
    ss << "\r\n";

    header = ss.str();
}

std::string HttpResponse::getSocketData() const
{
    std::stringstream ss;
    ss << header;
    ss << htmlContent;
    return ss.str();
}

void HttpResponse::sendTo(const ClientSocket &client) const
{
    std::string message = getSocketData();
    write(client.socket(), message.c_str(), message.size());
    printf("------------------ Message sent -------------------\n");
}

HttpRequest::HttpRequest():
    requestType (Request_Invalid),
    path        ("")
{
}

RequestType HttpRequest::getType() const
{
    return requestType;
}

void HttpRequest::parseData(std::string data)
{
    if (data.size() == 0)
    {
        requestType = Request_Invalid;
        return;
    }

    while (data.size() > 0 && (data[0] == '\r' || data[0] == '\n'))
    {
        data = data.substr(1);
    }

    size_t spacePos = data.find(' ');
    if (spacePos == std::string::npos)
    {
        requestType = Request_Invalid;
        return;
    }
    std::string type = data.substr(0, spacePos);
    if (type.compare("GET") == 0)
    {
        requestType = Request_Get;
        size_t pathPos = data.find(' ', spacePos + 1);
        if (pathPos == std::string::npos)
        {
            requestType = Request_Invalid;
            return;
        }
        path = data.substr(spacePos + 1, pathPos - spacePos - 1);
        printf(std::string("GET request @ path: " + path + "\n").c_str());
    }
    else if (type.compare("POST") == 0)
    {
        requestType = Request_Post;
    }
    else
    {
        requestType = Request_Invalid;
    }
}

std::string HttpRequest::getPath() const
{
    return path;
}

void HttpRequest::read(const ClientSocket &client)
{
    char buffer[30000] = {0};
    long valread = ::read( client.socket() , buffer, 30000);
    printf("%s\n",buffer );

    parseData(buffer);
}
