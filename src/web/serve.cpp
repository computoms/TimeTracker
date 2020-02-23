#include "webserver.h"

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sstream>

/**
 * Main program to start the web server.
 */
int main()
{
    WebServer server;
    server.initialize("127.0.0.1", 8080);
    server.start();
    server.stop();
    server.shutdown();
    return 0;
}