#include "server_socket.hpp"
#include <iostream>
#include "game.hpp"

ServerSocket::ServerSocket(int port)
{
    service_port = port;
}

void ServerSocket::service()
{
    int last_print = 0;
    while (game.getGameRunningTime() < 20)
    {
        if (game.getGameRunningTime() > last_print + 1)
        {
            std::cout << "#Server_Thread working real hard" << std::endl;
            last_print = game.getGameRunningTime();
        }
    }
}

void ServerSocket::start()
{
    socket_thread = ThreadPtr(new std::thread(&ServerSocket::service, this));
    socket_thread->join();
     
}

void ServerSocket::handleRequest()
{
}

int ServerSocket::getPort()
{
    return service_port;
}

