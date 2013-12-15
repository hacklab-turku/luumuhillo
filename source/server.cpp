#include "server.hpp"

Server::Server()
{
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
   return -1; 
}


