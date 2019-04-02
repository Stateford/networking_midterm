#include "init.h"

#include <thread>
#include <windowsx.h>

#include "resource.h"
#include "controls\listView.h"
#include "controls\button.h"
#include "controls\popupMenu.h"
#include "config.h"
#include "controller.h"
#include "utils.h"
#include "messages.h"

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
            .setSize(500, 820)
            .setStyleMask(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS)
            .create();

        authorBookView->setPosition(840, 20)
            .setSize(200, 550)
            .setStyleMask(WS_CHILD | WS_VISIBLE | LVS_REPORT)
            .create();

        bookView->setPosition(840, 300)
            .setSize(200, 550)
            .setStyleMask(WS_CHILD | WS_VISIBLE | LVS_REPORT)
            .create();

        refreshButton->setPosition(200, 650)
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
            if (authors->size() == 0)
                return;
            const unsigned int index = SendMessage(authorView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
            if (index > authors->size())
                return;
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
                try
                {
                    const unsigned int authIndex = SendMessage(authorView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
                    auto auths = *authors;
                    Pubs::Author author = auths[authIndex];

                    Pubs::Controller::deleteAuthor(author);

                    authorView->callback();
                }
                catch (std::exception e)
                {
                    auto err = Utils::utf8_to_utf16(e.what());
                    MessageBox(NULL, err.c_str(), L"Error", MB_OK);
                }
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
                try 
                {
                    const int authIndex = SendMessage(authorView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
                    const int bookIndex = SendMessage(authorBookView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
                    if (authIndex <= -1 || bookIndex <= -1)
                        return;

                    auto auths = *authors;
                    Pubs::Author author = auths[authIndex];


                    auto bookVec = *authorBooks;
                    Pubs::Book book = bookVec[bookIndex];

                    Pubs::Controller::removeBookAuthor(author, book);
                    authorView->callback();
                }
                catch (std::exception e)
                {
                    auto err = Utils::utf8_to_utf16(e.what());
                    MessageBox(NULL, err.c_str(), L"Error", MB_OK);
                }
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
                try 
                {
                    const int authIndex = SendMessage(authorView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);
                    const int bookIndex = SendMessage(bookView->getHandle(), LVM_GETNEXTITEM, (WPARAM)-1, (LPARAM)LVNI_SELECTED);

                    if (authIndex <= -1 || bookIndex <= -1)
                        return;

                    auto auths = *authors;
                    Pubs::Author author = auths[authIndex];

                    auto bookVec = *books;
                    Pubs::Book book = bookVec[bookIndex];

                    Pubs::Controller::addBookToAuthor(author, book);
                    authorView->callback();
                }
                catch (std::exception e)
                {
                    auto err = Utils::utf8_to_utf16(e.what());
                    MessageBox(NULL, err.c_str(), L"Error", MB_OK);
                }

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

        std::thread([=]() {
        RETRY_PRESSED:
            try
            {
                *authors = Pubs::Controller::getAllAuthors();
                authorView->clear();

                for (const auto &p : *authors)
                {
                    std::string contract = p.contract ? "yes" : "no";
                    authorView->addRow({ p.au_fname.c_str(), p.au_lname.c_str(), p.phone.c_str(), p.address.c_str(), p.state.c_str(), p.city.c_str(), p.zip.c_str(), contract });
                }
            }
            catch (std::exception err)
            {
                unsigned int result = MessageBox(NULL, L"Could not connect to the server", L"Error", MB_RETRYCANCEL | MB_SYSTEMMODAL);
                goto RETRY_PRESSED;
            }
        }).detach();
    }

    void getAuthorData(AuthorControls controls, Pubs::Author* author)
    {
        std::string au_fname(50, '\0');
        std::string au_lname(50, '\0');
        std::string au_phone(50, '\0');
        std::string au_addr(50, '\0');
        std::string au_state(50, '\0');
        std::string au_city(50, '\0');
        std::string au_zip(50, '\0');

        GetWindowTextA(controls.edit_auth_fname, &au_fname[0], 50);
        GetWindowTextA(controls.edit_auth_lname, &au_lname[0], 50);
        GetWindowTextA(controls.edit_auth_phone, &au_phone[0], 50);
        GetWindowTextA(controls.edit_auth_addr, &au_addr[0], 50);
        GetWindowTextA(controls.edit_auth_state, &au_state[0], 50);
        GetWindowTextA(controls.edit_auth_city, &au_city[0], 50);
        GetWindowTextA(controls.edit_auth_zip, &au_zip[0], 50);

        const unsigned int contract = ComboBox_GetCurSel(controls.edit_auth_contract);

        author->au_fname = au_fname;
        author->au_lname = au_lname;
        author->address = au_addr;
        author->phone = au_phone;
        author->state = au_state;
        author->city = au_city;
        author->zip = au_zip;
        author->contract = static_cast<bool>(contract);
    }

    // Message handler for main window
    INT_PTR CALLBACK Author(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        UNREFERENCED_PARAMETER(lParam);
        static Pubs::Author *author;
        static AuthorControls AuthorCtrl{ 0 };

        static bool edit;

        switch (message)
        {
        case WM_INITDIALOG:
            // pass data to auth

            AuthorCtrl.edit_auth_id = GetDlgItem(hDlg, IDC_AUTH_ID);
            AuthorCtrl.edit_auth_fname = GetDlgItem(hDlg, IDC_AUTH_FNAME);
            AuthorCtrl.edit_auth_lname = GetDlgItem(hDlg, IDC_AUTH_LNAME);
            AuthorCtrl.edit_auth_phone = GetDlgItem(hDlg, IDC_AUTH_PHONE);
            AuthorCtrl.edit_auth_addr = GetDlgItem(hDlg, IDC_AUTH_ADDR);
            AuthorCtrl.edit_auth_state = GetDlgItem(hDlg, IDC_AUTH_STATE);
            AuthorCtrl.edit_auth_city = GetDlgItem(hDlg, IDC_AUTH_CITY);
            AuthorCtrl.edit_auth_zip = GetDlgItem(hDlg, IDC_AUTH_ZIP);
            
            AuthorCtrl.edit_auth_contract = GetDlgItem(hDlg, IDC_AUTH_CONTRACT);

            ComboBox_AddString(AuthorCtrl.edit_auth_contract, L"No");
            ComboBox_AddString(AuthorCtrl.edit_auth_contract, L"Yes");

            if (lParam)
            {
                edit = true;
                author = (Pubs::Author*)lParam;

                const auto au_id = Utils::utf8_to_utf16(author->au_id);
                const auto fname = Utils::utf8_to_utf16(author->au_fname);
                const auto lname = Utils::utf8_to_utf16(author->au_lname);
                const auto phone = Utils::utf8_to_utf16(author->phone);
                const auto addr = Utils::utf8_to_utf16(author->address);
                const auto state = Utils::utf8_to_utf16(author->state);
                const auto city = Utils::utf8_to_utf16(author->city);
                const auto zip = Utils::utf8_to_utf16(author->zip);

                const unsigned int contract = static_cast<unsigned int>(author->contract);

                Edit_SetText(AuthorCtrl.edit_auth_id, au_id.c_str());
                Edit_SetText(AuthorCtrl.edit_auth_fname, fname.c_str());
                Edit_SetText(AuthorCtrl.edit_auth_lname, lname.c_str());
                Edit_SetText(AuthorCtrl.edit_auth_phone, phone.c_str());
                Edit_SetText(AuthorCtrl.edit_auth_addr, addr.c_str());
                Edit_SetText(AuthorCtrl.edit_auth_state, state.c_str());
                Edit_SetText(AuthorCtrl.edit_auth_city, city.c_str());
                Edit_SetText(AuthorCtrl.edit_auth_zip, zip.c_str());

                ComboBox_SetCurSel(AuthorCtrl.edit_auth_contract, contract);
            }
            else
            {
                edit = false;
                author = new Pubs::Author();

                auto au_id = Utils::utf8_to_utf16(author->au_id);
                Edit_SetText(AuthorCtrl.edit_auth_id, au_id.c_str());
            }
            return (INT_PTR)TRUE;

        case WM_COMMAND:
            const unsigned int wMsg = LOWORD(wParam);

            switch (wMsg)
            {
            case IDOK:
            {
                if (edit)
                {
                    getAuthorData(AuthorCtrl, author);
                    try
                    {
                        Pubs::Controller::editAuthor(*author);
                    }
                    catch (std::exception e)
                    {
                        auto err = Utils::utf8_to_utf16(e.what());
                        MessageBox(NULL, err.c_str(), L"Error", MB_OK);
                        goto AUTH_ERR;
                    }
                }
                else
                {
                    getAuthorData(AuthorCtrl, author);
                    try 
                    {
                        Pubs::Controller::createAuthor(*author);
                    }
                    catch (std::exception e)
                    {
                        auto err = Utils::utf8_to_utf16(e.what());
                        MessageBox(NULL, err.c_str(), L"Error", MB_OK);
                        goto AUTH_ERR;
                    }
                    delete author;
                }
                const HWND parent = GetParent(hDlg);
                SendMessage(parent, REFRESH_VIEWS, 0, 0);
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            }
            case IDCANCEL:
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;
            default:
                break;
            }
            break;
        }
AUTH_ERR:
        return (INT_PTR)FALSE;
    }
}