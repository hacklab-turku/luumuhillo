#include "server_socket.hpp"
#include <iostream>
#include "game.hpp"
#include "server.hpp"
#include "networked_input.hpp"

ServerSocket::ServerSocket(int port)
{
    service_port = port;
    finishedMutex = MutexPtr(new std::mutex());
    socket = UdpSocketPtr(new sf::UdpSocket());
    socket->setBlocking(false);
    finished = false;
}

void ServerSocket::service()
{
    if (socket->bind(service_port) != sf::Socket::Status::Done)
    {
        std::cout << "!ServerSocket: Error opening socket at port " << service_port << std::endl;
        reportFinished();
        return;
    }
    std::cout << "#ServerSocket: socket up at port " << service_port << std::endl;

    // Verify client knows we are here
    char buffer[1024];
    std::size_t received_count = 0;
    

    int wait_duration = 100000;
    long wait_start = game.getGameRunningTime();
 
    bool got_response = false;

    while ((game.getGameRunningTime() < wait_start + wait_duration) && !got_response)
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
        reportFinished();
        return;
    }

    while (!getFinished())
    {
        // First check if the server has anything to send to the client

        if (game.getServer()->stateHasChanged())
        {
            sendDeltas();
        }

        // Then receive the client's information

        if (socket->receive(buffer, sizeof(buffer), received_count, sender, senderPort) != sf::Socket::Done)
        {
        }
        else
        {
            std::cout << "#ServerThread: Client told us: " << buffer <<" first char: " << buffer[0] <<  std::endl;
            if (buffer[0] == 'u')
                game.getNetworkedInput()->up(service_port);
            else if (buffer[0] == 'd')
                game.getNetworkedInput()->down(service_port);
            else if (buffer[0] == 'l')
                game.getNetworkedInput()->left(service_port);
            else if (buffer[0] == 'r')
                game.getNetworkedInput()->right(service_port);
            else if (buffer[0] == 'x')
                reportFinished();
        }

    }

    std::cout << "#Server_thread: Exiting safely" << std::endl;
}

void ServerSocket::sendDeltas()
{
    game.getServer()->getDeltas();
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
    return out;
}

void ServerSocket::join()
{
    socket_thread->join();    
}

void ServerSocket::handleRequest()
{
}

int ServerSocket::getPort()
{
    return service_port;
}

