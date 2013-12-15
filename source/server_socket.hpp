#ifndef __SERVERSOCKET_HPP_
#define __SERVERSOCKET_HPP_

#include "typedefs.hpp"

class ServerSocket
{
private:
    int service_port;
    UdpSocketPtr socket;
    ThreadPtr socket_thread;
public:
    ServerSocket(int port);

    void service();
    void start();
    void handleRequest();
    int getPort();
};

#endif

