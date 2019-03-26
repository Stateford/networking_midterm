#pragma once

#include <string>
#include <nlohmann\json.hpp>

namespace Pubs
{
    using namespace nlohmann;
    class Author
    {
    private:
        std::string _au_id;
        std::string _au_lname;
        std::string _au_fname;
        std::string _phone;
        std::string _address;
        std::string _state;
        std::string _city;
        std::string _zip;
        bool _contract;
    public:
        Author(json);
    };
}