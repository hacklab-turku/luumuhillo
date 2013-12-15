#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <sstream>

int send_initial()
{
    // Ask for the server address
    sf::IpAddress server;
    server = "localhost";

    // Create a socket for communicating with the server
    sf::UdpSocket socket;

    std::string sendData = "hello";
    char* out = sendData.c_str();

    int port = 15000;

    std::cout << "sending message to server" << std::endl;
    if (socket.send(out, sizeof(out), server, port) != sf::Socket::Done)
        return;
    std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;

    // Receive an answer from anyone (but most likely from the server)
    char in[1024];
    std::size_t received;
    sf::IpAddress sender;
    unsigned short senderPort;
    if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
        return;
    std::cout << "Message received from " << sender << ": \"" << in << "\"" << std::endl;

    std::stringstream ss;

    ss << in;

    int out_port = 0;
    ss >> out_port;

    return out_port;
}


void start_main_socket(int port)
{
    sf::UdpSocket socket;
    socket.setBlocking(false);

    char buffer[1024];
    std::size_t received_count = 0;
    sf::IpAddress target = "localhost";
    

    if (socket.send(buffer, sizeof(buffer), target, port) != sf::Socket::Done)
    {
        std::cout << "no go " << std::endl;
        return;
    }
    else
    {
        std::cout << "go" << std::endl;
    }

    // Keep looping, send key presses
    bool done = false;
    std::string input = "u";
    char* to_send = input.c_str();
    while (!done)
    {
        std::cin >> input;
        to_send[0] = input.c_str();
        if (socket.send(to_send, sizeof(char), target, port) != sf::Socket::Done)
        {
            std::cout << "error sending keys: "  << to_send << std::endl;
        }
        else
        {
            std::cout << "sent key press: " << to_send << std::endl;
        }

        if (to_send[0] == 'x')
            done = true;

    }

}

int main(int argc, char** argv)
{
    int port = send_initial();
    std::cout << "Got port number " << port << std::endl;

    start_main_socket(port);

    return 0;
}

