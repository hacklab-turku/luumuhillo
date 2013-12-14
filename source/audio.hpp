#ifndef __AUDIO_HPP_
#define __AUDIO_HPP_

#include <string>
#include <SFML/Audio.hpp>
#include "typedefs.hpp"

class Audio
{
private:
    float standard_volume;
public:
    Audio();
    void playsound(std::string name);
};

#endif
