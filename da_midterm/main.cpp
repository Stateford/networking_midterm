#include <iostream>
#include "config\config.h"
#include "network\URL.h"
#include "network\request.h"
#include "network\headers.h"
#include <nlohmann\json.hpp>

int main()
{
    Network::Request req(std::string("http://clayserver.myddns.me:8090/authors"));
    std::string response;
    req.method(Network::GET)->request(&response);

    /*
    HTTP/1.1 304 Not Modified
    X-Powered-By: Express
    ETag: W/"106e-/SW42zJafGv2jtxA59LjoB0KAro"
    Date: Tue, 12 Mar 2019 20:44:20 GMT
    Connection: keep-alive
    */


    std::cout << headers[1] << std::endl;
    return 0;
}