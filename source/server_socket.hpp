#ifndef __SERVERSOCKET_HPP_
#define __SERVERSOCKET_HPP_

#include "typedefs.hpp"

class ServerSocket
{
private:
    int port;
    UdpSocketPtr socket;
public:
    ServerSocket();

    void handleRequest();
};

#endif

