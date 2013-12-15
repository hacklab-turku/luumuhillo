#ifndef __SERVER_HPP_
#define __SERVER_HPP_

#include "typedefs.hpp"

class Server
{
private:
    std::vector<UdpSocketPtr> sockets;
    unsigned int number_of_clients;
    unsigned int max_clients;
    std::string master_address;
    int master_port;
    int starting_port_range;

    UdpSocketPtr master_socket;

public:
    Server();

    void init();
    int openSocket();
    void closeSocket(int id);
    void handleRequest(char* req);
    std::string giveMasterAddress();
    int giveMasterPort();
};

#endif

