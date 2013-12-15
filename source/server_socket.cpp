#include "server_socket.hpp"
#include <iostream>
#include "game.hpp"

ServerSocket::ServerSocket(int port)
{
    service_port = port;
    finishedMutex = MutexPtr(new std::mutex());
}

void ServerSocket::service()
{
    int last_print = 0;
    while (game.getGameRunningTime() < 20)
    {
        if (game.getGameRunningTime() > last_print + 1)
        {
            std::cout << "#server_thread working real hard" << std::endl;
            last_print = game.getGameRunningTime();
        }
    }
    reportFinished();
    std::cout << "#Server_thread: Exiting safely" << std::endl;
}

void ServerSocket::start()
{
    std::cout << "#ServerSocket: Launching thread" << std::endl;
    socket_thread = ThreadPtr(new std::thread(&ServerSocket::service, this));
}

void ServerSocket::reportFinished()
{
    finishedMutex->lock();
    finished = true;
    finishedMutex->unlock();
}

bool ServerSocket::getFinished()
{
    bool out;
    finishedMutex->lock();
    out = finished;
    finishedMutex->unlock();
}

void ServerSocket::handleRequest()
{
}

int ServerSocket::getPort()
{
    return service_port;
}

