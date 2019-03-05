#pragma once

#include <string>

namespace Config 
{
    class Config {
    private:
        const std::string CONFIG_PATH = "config.txt";
    public:
        static std::string HOSTNAME;
        Config();
        ~Config();

        void parseEnv();
        void parseFile();
    };
}