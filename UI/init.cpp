#include "init.h"

#include <thread>

#include "resource.h"
#include "controls\listView.h"
#include "controls\button.h"
#include "controls\popupMenu.h"
#include "config.h"
#include "controller.h"

namespace UI
{
    enum AUTHORMENU {
        CREATE = 1,
        EDIT,
        REMOVE
    };

    enum AUTHORBOOKMENU {
        REMOVEBOOK = 1
    };

    enum BOOKMENU {
        ADDBOOK = 1
    };

    void init(HWND hWnd, std::vector<Pubs::Author> *authors, std::vector<Pubs::Book> *books, std::vector<Pubs::Book> *authorBooks)
    {
        Config::Config config;

        auto refreshButton = new Controls::Button(hWnd);
        auto authorView = new Controls::ListView(hWnd);
        auto bookView = new Controls::ListView(hWnd);
        auto authorBookView = new Controls::ListView(hWnd);
        
        // context menus
        auto authorMenu = new Controls::PopupMenu(hWnd);
        auto authorBookMenu = new Controls::PopupMenu(hWnd);
        auto bookMenu = new Controls::PopupMenu(hWnd);

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
        });

        const std::vector<std::wstring> &bookHeader = {L"Title", L"type", L"Published", L"Price", L"Notes"};

        authorView->setHeaders({ L"First Name", L"Last Name", L"phone", L"address", L"state", L"city", L"zip", L"contract" });
        bookView->setHeaders(bookHeader);
        authorBookView->setHeaders(bookHeader);

        authorMenu->setParentMessage(authorView->messageId);
        authorMenu->setOptions({ L"Create", L"Edit", L"Remove" }).create();

        authorMenu->registerCallback([=]() {
            switch (authorMenu->index)
            {
            case AUTHORMENU::CREATE:
                DialogBox(NULL, MAKEINTRESOURCE(IDD_AUTHORS), hWnd, Author);
                break;
            case AUTHORMENU::EDIT:
            {
                const unsigned int authIndex = SendMessage(authorView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
                auto auths = *authors;
                Pubs::Author *author = &auths[authIndex];

                DialogBoxParam(NULL, MAKEINTRESOURCE(IDD_AUTHORS), hWnd, Author, (LPARAM)author);
            }
                break;
            case AUTHORMENU::REMOVE:
            {
                const unsigned int authIndex = SendMessage(authorView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
                auto auths = *authors;
                Pubs::Author author = auths[authIndex];

                Pubs::Controller::deleteAuthor(author);

                authorView->callback();
            }
                break;
            default:
                break;
            }
        });

        authorBookMenu->setParentMessage(authorBookView->messageId);
        authorBookMenu->addOption(L"Remove").create();

        authorBookMenu->registerCallback([=]() {
            switch (authorBookMenu->index)
            {
            case AUTHORBOOKMENU::REMOVEBOOK:
            {
                const unsigned int authIndex = SendMessage(authorView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
                auto auths = *authors;
                Pubs::Author author = auths[authIndex];

                const unsigned int bookIndex = SendMessage(authorBookView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
                auto bookVec = *authorBooks;
                Pubs::Book book = bookVec[bookIndex];

                Pubs::Controller::removeBookAuthor(author, book);
                authorView->callback();
                break;
            }
            break;
            default:
                break;
            }
        });
        
        bookMenu->setParentMessage(bookView->messageId);
        bookMenu->addOption(L"Add Book to Author").create();

        bookMenu->registerCallback([=]() {
            switch (bookMenu->index)
            {
            case BOOKMENU::ADDBOOK:
            {
                const unsigned int authIndex = SendMessage(authorView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
                auto auths = *authors;
                Pubs::Author author = auths[authIndex];

                const unsigned int bookIndex = SendMessage(bookView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
                auto bookVec = *books;
                Pubs::Book book = bookVec[bookIndex];

                Pubs::Controller::addBookToAuthor(author, book);
                authorView->callback();
                break;
            }
            break;
            default:
                break;
            }
        });


        // add books to view
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


    // Message handler for main window
    INT_PTR CALLBACK Author(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        UNREFERENCED_PARAMETER(lParam);
        static Pubs::Author *author;

        switch (message)
        {
        case WM_INITDIALOG:
            // pass data to auth
            if (lParam)
            {
                author = (Pubs::Author*)lParam;
            }
            else
            {
                auto auth = Pubs::Author();
                author = &auth;
            }
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            const unsigned int wMsg = LOWORD(wParam);

            switch (wMsg)
            {
            case IDOK:
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            case IDCANCEL:
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            default:
                break;
            }
            break;
        }
        return (INT_PTR)FALSE;
    }
}