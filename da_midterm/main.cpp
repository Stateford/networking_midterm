#include <iostream>
#include "config\config.h"
#include "network\URL.h"
#include "network\network.h"

int main()
{
    Network::Request req(std::string("http://google.com/test"));
    return 0;
}