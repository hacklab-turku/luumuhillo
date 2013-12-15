#include "server.hpp"
#include "game.hpp"
#include <iostream>
#include "server_socket.hpp"
#include "toolbox.hpp"

Server::Server()
{
    number_of_clients = 0;
    checkDuration = 200;
    lastChecked = 0;
    running = true;
    max_clients = 8;
    master_port = 15000;
    starting_port_range = 16000;

    delta_mutex = MutexPtr(new std::mutex());
    changed_mutex = MutexPtr(new std::mutex());

}

void Server::init()
{
    master_socket = UdpSocketPtr(new sf::UdpSocket());
    master_socket->setBlocking(false);

    if (master_socket->bind(master_port) != sf::Socket::Status::Done)
    {
       std::cout << "!Server: Error opening master socket at port " << master_port << std::endl; 
    }
    std::cout << "#Server: Master socket up at port " << master_port << std::endl;
}

int Server::start()
{
    return mainloop();
}

int Server::mainloop()
{
    while (running)
    {
        if (game.isRunning())
            process_game();
        else
            running = false;
        process_requests();
        cleanup();
    }
    return 0;
}

void Server::process_game()
{
    game.loop();
}

void Server::process_requests()
{
    // Handle any connections that come to the master socket

    char buffer[1024];
    std::size_t received_count = 0;
    sf::IpAddress sender;
    unsigned short senderPort;

    if (master_socket->receive(buffer, sizeof(buffer), received_count, sender, senderPort) != sf::Socket::Done)
    {
       //std::cout << "no news" << std::endl; 
    }
    else
    {
        std::cout << "news!!!!!!!!!" << std::endl;
        std::string out = "";
        int assignedPort = openSocket();
        out = game.getToolbox()->intToString(assignedPort);
        std::cout << "#Server: Assigned port " << assignedPort << " to client " << sender << std::endl;
        char* outc = out.c_str();
        std::cout << outc << std::endl;
        if (master_socket->send(outc, sizeof(char)*out.size(), sender, senderPort) != sf::Socket::Done)
        {
            std::cout << "!Server: Could not transmit response" << std::endl;
        }
        else
        {
            std::cout << "#Server: Response sent to client" << std::endl;
        }
    }
    
}

void Server::cleanup()
{
    checkFinishedSockets();    
}

bool Server::stateHasChanged()
{
    changed_mutex->lock();
    changed_mutex->unlock();
}

void Server::getDeltas()
{
    delta_mutex->lock();
    delta_mutex->unlock();
}


void Server::handleRequest(char* data)
{

}

/**
* Takes a socket ID as parameter and closes that socket
* Message is sent to the client responding to this socket
* The socket is then removed from socketvector
*/
void Server::closeSocket(int id)
{
    
}

/**
* Attempts to open a new UDP socket
* Stores the new socket in socketcontainer and returns the id
* Returns -1 if failed
*/
int Server::openSocket()
{

    if (number_of_clients >= max_clients)
    {
        std::cout << "!Server: Error opening new socket: out of sockets " << number_of_clients << "/" << max_clients << std::endl;
        return -1;
    }
    std::cout << "#Server: Opening socket" << std::endl;
    
    number_of_clients++;
    int next_port = starting_port_range + number_of_clients;
    std::cout << "#Server: Next free port was: " << next_port << std::endl;

    ServerSocketPtr service_socket = ServerSocketPtr(new ServerSocket(next_port));    

    sockets.push_back(service_socket);
    std::cout << "#Server: Starting socket" << std::endl;
    return startSocket(next_port);
}

/**
* Launches a newly assigned socket and leaves it in its own thread
* Returns the port number if successful, -1 if failure
*/
int Server::startSocket(int port)
{
    auto s = std::find_if(sockets.begin(), sockets.end(),
            [port](ServerSocketPtr so) { return so->getPort() == port; } );
    if (s == sockets.end())
    {
        std::cout << "!Server: Can't start socket: Port not found in created sockets: " << port << std::endl;
        return -1;
    }
    (*s)->start();
    return port;
}

void Server::checkFinishedSockets()
{
    if (game.getGameRunningTime() > lastChecked + checkDuration)
    {
        lastChecked = game.getGameRunningTime();
        auto iter = std::find_if(sockets.begin(), sockets.end(),
            [](ServerSocketPtr s){ return s->getFinished(); });
        if (iter != sockets.end())
        {
            std::cout << "#Server: Removed finished socket at port " << (*iter)->getPort() << std::endl;
            (*iter)->join();
            sockets.erase(iter);
        }
    }
}

std::string Server::giveMasterAddress()
{
    return master_address;
}

int Server::giveMasterPort()
{
    return master_port;
}


