#include "configreader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "game.hpp"
#include <SFML/Graphics.hpp>

ConfigReader::ConfigReader()
{
    configFilePath = "config.txt";
}

/**
* Reads the game's config file and tells the Game about some hard-coded matters
* This is, for example, the game's desired resolution
* Returns 0 if successful
*/
int ConfigReader::readConfig()
{
    std::ifstream inputStream(configFilePath);
    std::string line;
    bool readResolution = false;
    int reso_x = 0;
    int reso_y = 0;
    std::stringstream reso_x_ss;
    std::stringstream reso_y_ss;
    int pos = 0;
    if (inputStream.is_open())
    {
        while (inputStream.good())
        {
            std::getline(inputStream, line);
            if (readResolution == true)
            {
                int x_is_at = line.find('x', pos);
                for (int i = 0; i < x_is_at; i++)
                {
                    reso_x_ss << line[i];
                }
                for (int i = x_is_at+1; i < line.size(); i++)
                {
                    reso_y_ss << line[i];
                }
                reso_x_ss >> reso_x;
                reso_y_ss >> reso_y;
            }
            if (line.compare("resolution") == 0)
                readResolution = true;
        }
        inputStream.close();
    }
    else
    {
        std::cout << "!ConfigReader: Error opening config file " << configFilePath << std::endl;
        return -1;
    }

    std::cout << "#ConfigReader: Resolution x: " << reso_x << " resolution y: " << reso_y << std::endl;
    game.setResolution(sf::Vector2i(reso_x, reso_y));
    return 0;
}
