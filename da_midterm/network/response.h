#pragma once

#include "headers.h"
#include "body.h"

namespace Network
{
    class Response
    {
    private:
        Headers _headers;
        Body _body;
        unsigned int _statusCode = 0;
    public:
        Response() {};

        void parseResponse(std::string);

        Body getBody();
        Headers getHeaders();
        std::string content();
    };
}