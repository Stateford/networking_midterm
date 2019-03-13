#include <iostream>
#include <nlohmann\json.hpp>
#include "config\config.h"
#include "network\URL.h"
#include "network\request.h"
#include "network\headers.h"
#include "network\response.h"

int main()
{
    Config::Config config;
    

    Network::Request req(config.HOSTNAME + std::string("/authors"));
    std::string response;
    response.reserve(10000);
    req.method(Network::GET)->request(&response);

    /*
    HTTP/1.1 304 Not Modified
    X-Powered-By: Express
    ETag: W/"106e-/SW42zJafGv2jtxA59LjoB0KAro"
    Date: Tue, 12 Mar 2019 20:44:20 GMT
    Connection: keep-alive
    */
    
    Network::Response res;
    res.parseResponse(response);
    
    try {
        auto j = nlohmann::json::parse(res.getBody().getBody());

        for (auto &p : j)
            std::cout << p << std::endl;
    }
    catch (nlohmann::json::exception e)
    {
        std::cout << res.getBody().getBody() << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << e.id << std::endl;
    }

    
    return 0;
}