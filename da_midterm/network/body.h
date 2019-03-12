#pragma once

#include <string>

namespace Network
{
    class Body
    {
    private:
        std::string _body;
    public:
        Body() {};
        Body(std::string body);

        void setBody(std::string);
        int length();
    };
}