#include "audio.hpp"
#include "datastorage.hpp"
#include "game.hpp"
#include <iostream>

Audio::Audio()
{
    standard_volume = 80.0f;
}

void Audio::playsound(std::string sound)
{
    SoundPtr soundfile = game.getDataStorage()->getSound(sound);
    if (soundfile == nullptr)
    {
        std::cout << "!Audio: Unable to play sound file: datastorage returned nullptr. Sound file was " << sound << std::endl;
        return;
    }

    soundfile->setVolume(80.0f);
    soundfile->play();
}
