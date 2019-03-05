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
        }
        else if (buffer.find("https://") != std::string::npos)
        {
            _protocol = HTTPS;
            buffer.replace(buffer.find("https://"), strlen("https://"), "");
        }
        else
        {
            _protocol = HTTP;
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
}