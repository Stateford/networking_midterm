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

    std::string Headers::get_headers()
    {
        std::string buffer;
        for (auto &p : _headers)
        {
            buffer += p.first + ": " + p.second + "\r\n";
        }

        return buffer;
    }

}