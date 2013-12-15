#include "server_socket.hpp"

ServerSocket::ServerSocket(int port)
{
    service_port = port;
}

void ServerSocket::start()
{
}

void ServerSocket::handleRequest()
{
}

int ServerSocket::getPort()
{
    return service_port;
}

