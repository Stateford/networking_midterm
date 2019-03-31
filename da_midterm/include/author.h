#pragma once

#include <string>
#include <nlohmann\json.hpp>

namespace Pubs
{
    using namespace nlohmann;
    using std::string;

    const unsigned char randomChar();

    class Author
    {
    private:
        void _generateId();
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

        Author();
        Author(json);

        json to_json();
    };
}