#include "response.h"
#include <algorithm>
#include <iostream>

namespace Network
{
    void Response::parseResponse(std::string response)
    {
        /*
        HTTP/1.1 304 Not Modified
        X-Powered-By: Express
        ETag: W/"106e-/SW42zJafGv2jtxA59LjoB0KAro"
        Date: Tue, 12 Mar 2019 20:44:20 GMT
        Connection: keep-alive
        */
        int header_end = response.find("\r\n\r\n");
        std::string header = response.substr(0, header_end);
        std::string delimiter = "\r\n";
        std::vector<std::string> headers;

        std::string::size_type pos = 0;
        std::string::size_type prev = 0;

        while ((pos = header.find(delimiter, prev)) != std::string::npos)
        {
            headers.push_back(header.substr(prev, pos - prev));
            prev = pos + delimiter.length();
        }
        std::string body = response.substr(header_end + 4);

        while (body.find(delimiter) != std::string::npos)
            body.replace(body.find(delimiter), delimiter.length(), "");

        _body.setBody(body);
    }

    Headers Response::getHeaders() 
    {
        return _headers;
    }

    Body Response::getBody() 
    {
        return _body;
    }
}