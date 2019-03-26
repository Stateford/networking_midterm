#include "URL.h"

namespace Network
{
    URL::URL() 
    {

    }

    URL::URL(std::string url)
    {
        _url = url;
        _parseUrl();
    }

    URL::URL(URL& other) 
    {
        _url = other._url;
        _hostname = other._hostname;
        _path = other._path;
        _protocol = other._protocol;
    }

    void URL::_parseUrl()
    {
        std::string buffer = _url;

        if (buffer.find("http://") != std::string::npos)
        {
            _protocol = HTTP;
            buffer.replace(buffer.find("http://"), strlen("http://"), "");
            if (buffer.find(":") != std::string::npos)
            {
                auto size = buffer.find_first_of("/") - buffer.find(':');
                _port = buffer.substr(buffer.find(":") + 1, size - 1);
                buffer.replace(buffer.find(":"), size, "");
            }
            else
                _port = "80";
        }
        else if (buffer.find("https://") != std::string::npos)
        {
            _protocol = HTTPS;
            buffer.replace(buffer.find("https://"), strlen("https://"), "");
            if (buffer.find(":") != std::string::npos)
            {
                auto size = buffer.size() - buffer.find(':');
                _port = buffer.substr(buffer.find(":") + 1, buffer.size() - buffer.find(":"));
                buffer.replace(buffer.find(":"), size, "");
            }
            else
                _port = "443";
        }
        else
        {
            _protocol = HTTP;
            if (buffer.find(":") >= 0)
            {
                auto size = buffer.size() - buffer.find(':');
                _port = buffer.substr(buffer.find(":") + 1, buffer.size() - buffer.find(":"));
                buffer.replace(buffer.find(":"), size, "");
            }
            else
                _port = "80";
        }
        

        if (buffer.find("/") == std::string::npos)
        {
            _hostname = buffer;
            _path = "/";
        }
        else
        {
            size_t position = buffer.find_first_of("/");
            _hostname = buffer.substr(0, position);
            _path = buffer.substr(position, buffer.length());
        }
    }

    void URL::parse(std::string url)
    {
        _url = url;
        _parseUrl();
    }

    std::string URL::getHostname() 
    {
        return _hostname;
    }
    
    std::string URL::getPath()
    {
        return _path;
    }

    Protocol URL::getProtocol()
    {
        return _protocol;
    }

    std::string URL::getUrl()
    {
        return _url;
    }

    std::string URL::getPort()
    {
        return _port;
    }
}