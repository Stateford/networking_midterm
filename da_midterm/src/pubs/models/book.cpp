#include "book.h"

#define JSON_STRING(x) x.get<string>()

namespace Pubs
{
    Book::Book(json j)
    {
        title_id = JSON_STRING(j["title_id"]);
        title = JSON_STRING(j["title"]);
        type = JSON_STRING(j["type"]);
        pub_name = JSON_STRING(j["pub_name"]);
        price = j["price"].get<double>();
        advance = j["advance"].get<double>();
        royalty = j["royalty"].get<int>();
        ytd_sales = j["ytd_sales"].get<int>();;
        notes = JSON_STRING(j["notes"]);
    }

    json Book::to_json()
    {
        json book = {
            {"title_id", title_id},
            {"title", title},
            {"type", type},
            {"pub_name", pub_name},
            {"price", price},
            {"advance", advance},
            {"royalty", royalty},
            {"ytd_sales", ytd_sales},
            {"notes", notes}
        };

        return book;
    }
}