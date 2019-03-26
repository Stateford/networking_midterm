#pragma once

#include <vector>
#include <string>


#include "models/author.h"
#include "models/book.h"

namespace Pubs
{
    using std::vector;
    using std::string;

    class Controller
    {
    public:
        static void createAuthor(Author);
        static void editAuthor(Author);
        static Author getAuthor(string);
        static void addBookToAuthor(Author, Book);
        static void addBookToAuthor(Author, vector<Book>);
        static void removeBookAuthor(Author, Book);
        static vector<Book> getAuthorBooks(Author);
        static vector<Author> getAllAuthors();
        static vector<Book> getAllBooks();
    };
}