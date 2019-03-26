#include "author.h"

namespace Pubs
{
    Author::Author(json j) 
    {
        _au_id = std::string(j["au_id"]);
        _au_lname = std::string(j["au_lname"]);
        _au_fname = std::string(j["au_fname"]);
        _phone = std::string(j["phone"]);
        _address = std::string(j["address"]);
        _state = std::string(j["state"]);
        _city = std::string(j["city"]);
        _zip = std::string(j["zip"]);
        _contract = j["contract"];
    }
}