/*
resource for uuid generation

https://lowrey.me/guid-generation-in-c-11/
*/

#include "author.h"

#include <random>


#define JSON_STRING(x) x.get<std::string>()

namespace Pubs
{
    Author::Author()
    {
        _generateId();
    }

    Author::Author(json j) 
    {
        au_id = JSON_STRING(j["au_id"]);
        au_lname = JSON_STRING(j["au_lname"]);
        au_fname = JSON_STRING(j["au_fname"]);
        phone = JSON_STRING(j["phone"]);
        address = JSON_STRING(j["address"]);
        state = JSON_STRING(j["state"]);
        city = JSON_STRING(j["city"]);
        zip = JSON_STRING(j["zip"]);
        contract = j["contract"].get<int>();
    }

    const unsigned char randomChar()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0x30, 0x39);
        return dis(gen);
    }

    void Author::_generateId()
    {
        const unsigned int uuid_breaks[] = { 3, 2, 4 };

        for (unsigned int i = 0; i < 3; i++)
        {
            for(unsigned int p = 0; p < uuid_breaks[i]; p++)
                au_id += randomChar();
            if (i == 2)
                break;
            au_id += "-";
        }
    }

    json Author::to_json()
    {
        const json author = {
            {"au_id", au_id},
            {"au_fname", au_fname},
            {"au_lname", au_lname},
            {"phone", phone},
            {"address", address},
            {"city", city},
            {"state", state},
            {"zip", zip},
            {"contract", contract}
        };

        return author;
    }
}