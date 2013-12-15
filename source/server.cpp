#include "server.hpp"
#include "game.hpp"
#include <iostream>
#include "server_socket.hpp"

Server::Server()
{
    number_of_clients = 0;
}

void Server::init()
{
    max_clients = 8;
    master_port = 15000;
    starting_port_range = 16000;

    master_socket = UdpSocketPtr(new sf::UdpSocket());

    if (master_socket->bind(master_port) != sf::Socket::Status::Done)
    {
       std::cout << "!Server: Error opening master socket at port " << master_port << std::endl; 
    }
    std::cout << "#Server: Master socket up at port " << master_port << std::endl;

    // test server socket creation with a dummy
    openSocket();

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

    ServerSocketPtr service_socket = ServerSocketPtr(new ServerSocket(next_port));    

    sockets.push_back(service_socket);
    std::cout << "#Server: Starting socket" << std::endl;
    return startSocket(next_port);
}

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
    return 0;
}

std::string Server::giveMasterAddress()
{
    return master_address;
}

int Server::giveMasterPort()
{
    return master_port;
}


