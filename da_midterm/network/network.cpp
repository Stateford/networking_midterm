#include "network.h"
#include <iostream>

namespace Network 
{
    Request::Request(URL url)
    {
        _url = url;
        std::cout << _url.getHostname() << std::endl;
        
    }

    Request::~Request()
    {

    }
}