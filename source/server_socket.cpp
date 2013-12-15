#include "server_socket.hpp"
#include <iostream>
#include "game.hpp"

ServerSocket::ServerSocket(int port)
{
    service_port = port;
    finishedMutex = MutexPtr(new std::mutex());
    socket = UdpSocketPtr(new sf::UdpSocket());
    socket->setBlocking(false);
}

void ServerSocket::service()
{
    if (socket->bind(service_port) != sf::Socket::Status::Done)
    {
       std::cout << "!ServerSocket: Error opening socket at port " << service_port << std::endl;
    }
    std::cout << "#ServerSocket: socket up at port " << service_port << std::endl;

    // Verify client knows we are here
    char buffer[1024];
    std::size_t received_count = 0;
    

    int wait_duration = 120;
    long wait_start = game.getGameRunningTime();
 
    bool got_response = false;

    while (game.getGameRunningTime() < wait_start + wait_duration)
    {
        if (socket->receive(buffer, sizeof(buffer), received_count, sender, senderPort) != sf::Socket::Done)
        {
            //std::cout << "no news" << std::endl; 
        }
        else
        {
            std::cout << "#ServerSocket: Got handshake from client. Continuing to loop" << std::endl;
            got_response = true;
        }
    }

    if (!got_response)
    {
        std::cout << "!SocketThread: Didn't get response from client in time during initial handshake" << std::endl;
        return;
    }

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

