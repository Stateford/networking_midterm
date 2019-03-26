#include "body.h"

namespace Network
{
    Body::Body(std::string body)
    {
        _body = body;
    }

    int Body::length()
    {
        return _body.length();
    }

    void Body::setBody(std::string body)
    {
        _body = body;
    }

    std::string Body::getBody()
    {
        return _body;
    }
}