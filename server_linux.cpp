#include "tcp_server.h"

int main()
{
    using namespace http;

    TcpServer server = TcpServer("0.0.0.0", 9006);
    server.startListen();

    return 0;
}