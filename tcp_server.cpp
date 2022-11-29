#include <tcp_server.h>

namespace http
{
    TcpServer::TcpServer()
    {
    }

    TcpServer::~TcpServer()
    {
    }

    int TcpServer::startServer()
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0)
        {
            exitWithError("Cannot create socket");
            return 1;
        }
        return 0;
    }
} 