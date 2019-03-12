#pragma once

#include <WinSock2.h>
#include <string>
#include <map>
#include <nlohmann\json.hpp>

#include "URL.h"
#include "socket.h"
#include "headers.h"
#include "body.h"
#include "response.h"

constexpr int DEFAULT_BUFLEN = 4095;

namespace Network
{
    enum Method {
        GET,
        POST,
        PUT,
        DEL
    };

    class Request {
    private:
        Socket _socket;
        ADDRINFOA _hints;
        ADDRINFOA *_result = NULL;
        ADDRINFOA *_ptr = NULL;
        Method _method;
        Headers _headers;
        Body _body;
        //Response _response;
        WSAData _wsaData;
        URL _url;
        void _getaddrinfo();
        void _buildHeader(Method, std::string*);
    public:
        Request(std::string);
        Request(URL);
        ~Request();

        Request* method(Method);
        Request* json(nlohmann::json);
        void request(std::string*);
        void request(nlohmann::json*);
    };
}