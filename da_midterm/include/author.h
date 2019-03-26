#pragma once

#include <string>
#include <nlohmann\json.hpp>

namespace Pubs
{
    using namespace nlohmann;
    using std::string;

    class Author
    {
    public:
        string au_id;
        string au_lname;
        string au_fname;
        string phone;
        string address;
        string state;
        string city;
        string zip;
        bool contract;

        Author(json);

        json to_json();
    };
}