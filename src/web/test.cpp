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
    server.initialize("127.0.0.1", PORT);
    server.start();
    server.stop();
    server.shutdown();
    return 0;
}