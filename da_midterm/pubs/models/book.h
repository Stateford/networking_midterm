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
        string book_id;
        Book(json);
    };
}