#ifndef __CLIENT_HPP_
#define __CLIENT_HPP_

#include "typedefs.hpp"

class Client
{
private:
    int service_port;
    std::string remote_master_address;
    int remote_master_port;
public:
    Client();

    int request_port();
    void initial_connection();
};

#endif

