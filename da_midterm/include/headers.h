#pragma once

#include <vector>
#include <string>
#include <map>

namespace Network
{
    class Headers
    {
    private:
        std::map<std::string, std::string> _headers;
    public:
        Headers();

        void addHeader(std::string, std::string);
        std::string& operator[](std::string);
        std::string getHeaders();
    };
}
