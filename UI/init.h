#pragma once

#include <Windows.h>
#include <vector>

#include "author.h"
#include "book.h"

namespace UI
{
    struct AuthorControls
    {
        HWND edit_auth_id;
        HWND edit_auth_fname;
        HWND edit_auth_lname;
        HWND edit_auth_phone;
        HWND edit_auth_addr;
        HWND edit_auth_state;
        HWND edit_auth_city;
        HWND edit_auth_zip;
        HWND edit_auth_contract;

    };

    void init(HWND, std::vector<Pubs::Author>*, std::vector<Pubs::Book>*, std::vector<Pubs::Book>*);
    void getAuthorData(AuthorControls, Pubs::Author*);

    INT_PTR CALLBACK Author(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
}