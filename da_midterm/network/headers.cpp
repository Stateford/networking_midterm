#include "headers.h"

namespace Network
{
    Headers::Headers()
    {
        _headers["Connection"] = "close";
    }

    std::string& Headers::operator[](std::string key)
    {
        return _headers[key];
    }

    std::string Headers::getHeaders()
    {
        std::string buffer;
        for (auto &p : _headers)
        {
            buffer += p.first + ": " + p.second + "\r\n";
        }

        return buffer;
    }

    void Headers::addHeader(std::string key, std::string value)
    {
        _headers[key] = value;
    }
}