#ifndef __SERVERSOCKET_HPP_
#define __SERVERSOCKET_HPP_

#include "typedefs.hpp"

class ServerSocket
{
private:
    int service_port;
    UdpSocketPtr socket;
    ThreadPtr socket_thread;
    bool finished;

    MutexPtr finishedMutex;
    sf::IpAddress sender;
    unsigned short senderPort;

public:
    ServerSocket(int port);

    void reportFinished();
    bool getFinished();
    void service();
    void start();

    void sendDeltas();

    void join();

    void handleRequest();
    int getPort();
};

#endif

