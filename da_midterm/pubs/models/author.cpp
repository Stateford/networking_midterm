#include "author.h"

#define JSON_STRING(x) x.get<std::string>()

namespace Pubs
{
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
        contract = j["contract"].get<bool>();
    }

    json Author::to_json()
    {
        json temp = {
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

        return temp;
    }
}