#pragma once

#include <Windows.h>
#include <vector>

#include "author.h"
#include "book.h"

namespace UI
{
    void init(HWND, std::vector<Pubs::Author>*, std::vector<Pubs::Book>*, std::vector<Pubs::Book>*);
    INT_PTR CALLBACK Author(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
}