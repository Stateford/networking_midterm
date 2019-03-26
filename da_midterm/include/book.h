#pragma once

#include <string>
#include <nlohmann\json.hpp>

namespace Pubs
{
    using namespace nlohmann;
    using std::string;

    class Book
    {
    public:
        string title_id;
        string title;
        string type;
        string pub_name;
        double price;
        double advance;
        int royalty;
        int ytd_sales;
        string notes;
        Book(json);

        json to_json();
    };
}