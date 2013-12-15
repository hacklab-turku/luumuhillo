#include "client.hpp"
#include "game.hpp"
#include "serverinfo.hpp"
#include <iostream>

Client::Client()
{
}

/**
* Makes a request to master server and asks for a port
* Returns the port number, or -1 if fail
*/
int Client::request_port()
{
    remote_master_port = game.getServerInfo()->master_port;
    remote_master_address = game.getServerInfo()->master_address;

    return -1;
}

/**
* Performs the initial request for the master server
* and sets up any pre-game things
*/
void Client::initial_connection()
{
    service_port = request_port();
    if (service_port == -1)
    {
        std::cout << "!Client: Could not get port from master server" << std::endl;
        return;
    }
    std::cout << "#Client: Master granted us port number " << service_port << std::endl;


}

