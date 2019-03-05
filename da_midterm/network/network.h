#pragma once

#ifdef _WIN32
#include <WinSock2.h>
#endif

#include <string>
#include <map>
#include "URL.h"

namespace Network
{
    enum Method {
        GET,
        POST,
        PUT,
        DEL
    };
    /*
    class Header {
    private:
        std::map<std::string, std::string> header;
    public:
        Header();
        
        void addHeader(std::string, std::string);
        std::string operator[] (std::string);
    };

    class Response {
    private:
        Header _header;
    public:
        Response();
    };
    */

    class Request {
    private:
        Method _method;
        //Header _header;
        //Response _response;
#ifdef _WIN32
        WSAData _wsaData;
#endif
        URL _url;
    public:
        Request(std::string);
        Request(URL);
        ~Request();
    };
}