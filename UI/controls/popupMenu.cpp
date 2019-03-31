#include "popupMenu.h"

#include <thread>

namespace Controls
{
    PopupMenu::~PopupMenu()
    {
        DestroyMenu(_menu); // free memory
    }

    void PopupMenu::create()
    {
        _menu = CreatePopupMenu();

        unsigned int count = 0;
        for (const auto &p : _options)
            AppendMenu(_menu, MF_STRING, ++count, p.c_str());
    }

    void PopupMenu::callback()
    {
        if (_hasCallBack)
        {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            index = TrackPopupMenu(_menu, TPM_RETURNCMD | TPM_LEFTALIGN | TPM_LEFTBUTTON, cursorPos.x, cursorPos.y, 0, _hwnd, 0);
            std::thread([=]() {
                _callback();
            }).detach();
        }
    }
}