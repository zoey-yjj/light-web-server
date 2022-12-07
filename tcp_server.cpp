#include <tcp_server.h>
#include <iostream>
#include <sstream>
#include <unistd.h>

namespace
{
    const int BUFFER_SIZE = 30720;

    void log(const std::string &message)
    {
        std::cout << message << std::endl;
    }

    void exitWithError(const std::string &errorMessage)
    {
        log("ERROR: " + errorMessage);
        exit(1);
    }
}

namespace http
{
    TcpServer::TcpServer(std::string ip_address, int port) : m_ip_address(ip_address), m_port(port), m_socket(), m_new_socket(),
                                                             m_incomingMessage(),
                                                             m_socketAddress(), m_socketAddress_len(sizeof(m_socketAddress)),
                                                             m_serverMessage(buildResponse())
    {
        m_socketAddress.sin_family = AF_INET;
        m_socketAddress.sin_port = htons(m_port);
        m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
        {
            startServer();
        }
    }

    TcpServer::~TcpServer()
    {
        closeServer();
    }


    int TcpServer::startServer()
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0)
        {
            exitWithError("Cannot create socket");
            return 1;
        }

        if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0)
        {
            exitWithError("Cannot connect socket to address");
            return 1;
        }

        return 0;
    }

    void TcpServer::closeServer()
    {
        close(m_socket);
        close(m_new_socket);
        exit(0);
    }

    void TcpServer::startListen()
    {
        if (listen(m_socket, 20) < 0)
        {
            exitWithError("Socket listen failed");
        }

        char buffer[BUFFER_SIZE] = {0};
        bytesReceived = read(m_new_socket, buffer, BUFFER_SIZE);

        if (bytesReceived < 0)
        {
            exitWithError("Failed to read bytes from client socket connection");
        }

        std::ostringstream ss;
        ss << "\n*** Listening on ADDRESS: " 
            << inet_ntoa(m_socketAddress.sin_addr) 
            << " PORT: " << ntohs(m_socketAddress.sin_port) 
            << " ***\n\n";
        log(ss.str());
    }

    void TcpServer::acceptConnection(SOCKET &new_socket)
    {
        new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, 
                            &m_socketAddress_len);
        if (new_socket < 0)
        {
            std::ostringstream ss;
            ss << "Server failed to accept incoming connection from ADDRESS: " 
            << inet_ntoa(m_socketAddress.sin_addr) << "; PORT: " 
            << ntohs(m_socketAddress.sin_port);
            exitWithError(ss.str());
        }
    }
} 