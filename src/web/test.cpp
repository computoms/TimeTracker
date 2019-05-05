#include "webserver.h"

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sstream>

#define PORT 8080

using namespace tt;

int main()
{
    WebServer server;
    server.initialize(0, PORT);
    server.start();
    return 0;
}