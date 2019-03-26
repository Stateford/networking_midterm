#pragma once

#include <string>

namespace Config 
{
    using std::string;

    class Config {
    private:
        const string CONFIG_PATH = "config.txt";
    public:
        static string HOSTNAME;
        Config();
        ~Config();

        void parseEnv();
        void parseFile();
    };
}