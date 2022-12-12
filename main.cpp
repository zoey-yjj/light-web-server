#include "server.h"

int main()
{
    Server server = Server("0.0.0.0", 9006);
    server.startListen();

    return 0;
}