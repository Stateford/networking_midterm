#include "init.h"

#include <thread>

#include "controls\control.h"
#include "config.h"
#include "controller.h"

namespace UI
{
    void init(HWND hWnd, std::vector<Pubs::Author> *authors, std::vector<Pubs::Book> *books, std::vector<Pubs::Book> *authorBooks)
    {
        Config::Config config;

        auto refreshButton = new Controls::Button(hWnd);
        auto authorView = new Controls::ListView(hWnd);
        auto bookView = new Controls::ListView(hWnd);
        auto authorBookView = new Controls::ListView(hWnd);

        authorView->setPosition(10, 20)
            .setSize(200, 810)
            .setStyleMask(WS_CHILD | WS_VISIBLE | LVS_REPORT)
            .create();

        authorBookView->setPosition(840, 20)
            .setSize(200, 550)
            .setStyleMask(WS_CHILD | WS_VISIBLE | LVS_REPORT)
            .create();

        bookView->setPosition(840, 300)
            .setSize(200, 550)
            .setStyleMask(WS_CHILD | WS_VISIBLE | LVS_REPORT)
            .create();

        refreshButton->setPosition(200, 300)
            .setSize(40, 100)
            .setStyleMask(WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON)
            .setText(L"Refresh")
            .create();

        authorView->setExStyleMask(LVS_EX_AUTOSIZECOLUMNS).setExStyleMask(LVS_EX_FULLROWSELECT);
        bookView->setExStyleMask(LVS_EX_AUTOSIZECOLUMNS).setExStyleMask(LVS_EX_FULLROWSELECT);
        authorBookView->setExStyleMask(LVS_EX_AUTOSIZECOLUMNS).setExStyleMask(LVS_EX_FULLROWSELECT);

        refreshButton->registerCallback([=]() {
            std::thread([=]() {
                *authors = Pubs::Controller::getAllAuthors();
                authorView->clear();

                for (auto const &p : *authors)
                {
                    std::string contract = p.contract ? "yes" : "no";
                    authorView->addRow({ p.au_fname.c_str(), p.au_lname.c_str(), p.phone.c_str(), p.address.c_str(), p.state.c_str(), p.city.c_str(), p.zip.c_str(), contract });
                }
            }).detach();
        });

        // author view on click
        authorView->registerCallback([=]() {
            std::thread([=]() {
                const unsigned int index = SendMessage(authorView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
                auto auths = *authors;
                Pubs::Author author = auths[index];
                *authorBooks = Pubs::Controller::getAuthorBooks(author);
                authorBookView->clear();
                
                for (auto const &p : *authorBooks)
                {
                    std::string price = std::to_string(p.price);
                    if (price.find('.') != std::string::npos)
                        price = price.substr(0, price.find('.') + 3);

                    authorBookView->addRow({ p.title.c_str(), p.type.c_str(), p.pub_name.c_str(), price.c_str(), p.notes.c_str() });
                }
            }).detach();
        });

        const std::vector<std::wstring> &bookHeader = {L"Title", L"type", L"Published", L"Price", L"Notes"};

        authorView->setHeaders({ L"First Name", L"Last Name", L"phone", L"address", L"state", L"city", L"zip", L"contract" });
        bookView->setHeaders(bookHeader);
        authorBookView->setHeaders(bookHeader);

        std::thread([=]() {
            *books = Pubs::Controller::getAllBooks();
            authorBookView->clear();

            for (auto const &p : *books)
            {
                std::string price = std::to_string(p.price);
                if (price.find('.') != std::string::npos)
                    price = price.substr(0, price.find('.') + 3);
                bookView->addRow({ p.title.c_str(), p.type.c_str(), p.pub_name.c_str(), price.c_str(), p.notes.c_str() });
            }

        }).detach();
    }
}