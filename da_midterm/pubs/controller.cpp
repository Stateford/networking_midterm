#include "controller.h"
#include "../config/config.h"
#include "..\network\request.h"
#include "..\network\headers.h"
#include "..\network\response.h"

namespace Pubs
{
    using namespace Network;

    vector<Author> Controller::getAllAuthors()
    {
        vector<Author> authors;
        Request request(Config::Config::HOSTNAME + "/authors");

        Response response = request.method(GET)->request();

        auto JSON = json::parse(response.content());

        for (auto &p : JSON)
            authors.push_back(Author(p));

        return authors;
    }

    vector<Book> Controller::getAllBooks()
    {
        vector<Book> books;
        Request request(Config::Config::HOSTNAME + "/book");

        Response response = request.method(GET)->request();

        auto JSON = json::parse(response.content());

        for (auto &p : JSON)
            books.push_back(Book(p));

        return books;
    }
}