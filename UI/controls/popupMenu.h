#pragma once

#include "control.h"

namespace Controls
{
    class PopupMenu : public Control
    {
    private:
        const wchar_t* _type = L"POPUPMENU";
        HMENU _menu;
        std::vector<std::wstring> _options;
    public:
        PopupMenu(HWND hwnd) : Control(hwnd) {};
        PopupMenu(int x, int y, int width, int height) : Control(x, y, width, height) {};
        ~PopupMenu();
        

        PopupMenu& addOption(std::wstring option) { _options.push_back(option); return *this; }
        PopupMenu& setOptions(std::vector<std::wstring> options) {_options = options; return *this;}

        HMENU getMenu() { return _menu; }

        void callback() override;
        void create() override;
    };
}