#ifndef __CONFIGREADER_HPP_
#define __CONFIGREADER_HPP_

#include <string>

class ConfigReader
{
private:
    std::string configFilePath;
public:
    ConfigReader();

    int readConfig();
};

#endif
