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

    nlohmann::json body = {
        {"au_id", "123-12-4211"},
        {"au_fname", "Test"},
        {"au_lname", "User"},
        {"phone", "123 123-1234"},
        {"address", "123 asdf"},
        {"city", "flavor town"},
        {"state", "12345"},
        {"zip", "12345"},
        {"contract", 1}
    };
    req.method(Network::POST)->json(body)->request(&response);
    

    
    Network::Response res;
    res.parseResponse(response);
    
    auto j = nlohmann::json::parse(res.content());

    for (auto &p : j)
        std::cout << p << std::endl;
    

    
    return 0;
}