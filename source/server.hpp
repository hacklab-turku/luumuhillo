#ifndef __SERVER_HPP_
#define __SERVER_HPP_

#include "typedefs.hpp"

class Server
{
private:
    std::vector<SocketPtr> sockets;
public:
    Server();

    int openSocket();
    void closeSocket(int id);
    void handleRequest(char* req);
};

#endif

