#ifndef __NETWORKEDINPUT_HPP_
#define __NETWORKEDINPUT_HPP_

class NetworkedInput
{
private:
public:
    NetworkedInput();

    void up(int player);
    void down(int player);
    void left(int player);
    void right(int player);
};

#endif

