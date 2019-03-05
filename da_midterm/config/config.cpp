#include "config.h"
#include <fstream>

namespace Config 
{
    std::string Config::HOSTNAME = "";

    Config::Config()
    {
        if (HOSTNAME.empty())
            parseFile();
    }

    Config::~Config()
    {

    }

    void Config::parseFile()
    {
        std::ifstream inFile(CONFIG_PATH);
        std::string buffer;
        inFile >> buffer;

        if (buffer.find("HOSTNAME=") >= 0)
            HOSTNAME = buffer.substr(buffer.find("=") + 1, buffer.length());
    }
}