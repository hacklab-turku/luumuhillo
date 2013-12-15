#ifndef __SERVERSOCKET_HPP_
#define __SERVERSOCKET_HPP_

#include "typedefs.hpp"

class ServerSocket
{
private:
    int service_port;
    UdpSocketPtr socket;
public:
    ServerSocket(int port);

    void start();
    void handleRequest();
    int getPort();
};

#endif

