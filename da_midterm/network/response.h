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
        unsigned int _statusCode;
    public:
        Response() {};

        void parseResponse(std::string);
    };


}