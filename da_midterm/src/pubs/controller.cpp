#include "controller.h"
#include "config.h"
#include "request.h"
#include "headers.h"
#include "response.h"

namespace Pubs
{
    using namespace Network;

    void Controller::checkError(json JSON)
    {
        if (JSON["status"].get<string>() == "error")
            throw std::exception(JSON["details"].get<string>().c_str());
    }

    vector<Author> Controller::getAllAuthors()
    {
        vector<Author> authors;
        Request request(Config::Config::HOSTNAME + "/authors");

        Response response = request.method(GET).request();

        auto JSON = json::parse(response.content());

        for (auto &p : JSON)
            authors.push_back(Author(p));

        return authors;
    }

    Author Controller::getAuthor(string au_id)
    {
        Request request(Config::Config::HOSTNAME + "/authors/" + au_id);

        Response response = request.method(GET).request();

        auto JSON = json::parse(response.content());
        
        // returns an array of authors
        return Author(JSON[0]);
    }

    void Controller::deleteAuthor(string au_id)
    {
        Request request(Config::Config::HOSTNAME + "/authors/" + au_id);

        Response response = request.method(DEL).request();

        auto JSON = json::parse(response.content());

        checkError(JSON);
    }

    void Controller::deleteAuthor(Author author)
    {
        Controller::deleteAuthor(author.au_id);
    }

    void Controller::editAuthor(Author author)
    {
        Request request(Config::Config::HOSTNAME + "/authors/" + author.au_id);

        Response response = request.method(PUT).json(author.to_json()).request();
        auto JSON = json::parse(response.content());

        checkError(JSON);
    }

    vector<Book> Controller::getAllBooks()
    {
        vector<Book> books;
        Request request(Config::Config::HOSTNAME + "/books");

        Response response = request.method(GET).request();

        auto JSON = json::parse(response.content());

        for (auto &p : JSON)
            books.push_back(Book(p));

        return books;
    }

    void Controller::createAuthor(Author author)
    {
        Request request(Config::Config::HOSTNAME + "/authors");
        Response response = request.method(POST).json(author.to_json()).request();

        auto JSON = json::parse(response.content());

        checkError(JSON);
    }

    vector<Book> Controller::getAuthorBooks(Author author)
    {
        vector<Book> books;
        Request request(Config::Config::HOSTNAME + "/authors/books/" + author.au_id);
        Response response = request.method(GET).request();

        auto JSON = json::parse(response.content());

        for (auto &p : JSON)
            books.push_back(Book(p));

        return books;
    }

    void Controller::addBookToAuthor(Author author, Book book)
    {
        Request request(Config::Config::HOSTNAME + "/authors/book/add");

        json body = {
            {"au_id", author.au_id},
            {"title_id", book.title_id}
        };
        Response response = request.method(PUT).json(body).request();

        auto JSON = json::parse(response.content());

        checkError(JSON);
    }

    void Controller::addBookToAuthor(Author author, vector<Book> books)
    {
        vector<string> bookIds;
        for (auto &p : books)
            bookIds.push_back(p.title_id);


        Request request(Config::Config::HOSTNAME + "/authors/books/");
        json body;
        body["au_id"] = author.au_id;
        body["title_id"] = bookIds;
 
        Response response = request.method(PUT).json(body).request();

        auto JSON = json::parse(response.content());
    }

    void Controller::removeBookAuthor(Author author, Book book) 
    {
        Request request(Config::Config::HOSTNAME + "/authors/book/remove");

        json body = {
            {"au_id", author.au_id},
            {"title_id", book.title_id}
        };

        Response response = request.method(PUT).json(body).request();
        auto JSON = json::parse(response.content());

        checkError(JSON);
    }
}