#pragma once

#include "control.h"
namespace Controls
{
    class ListView : public Control
    {
    private:
        const wchar_t* _type = WC_LISTVIEW;
        std::vector<std::wstring> _headers;
    public:
        ListView(HWND hwnd) : Control(hwnd) {};
        ListView(int x, int y, int width, int height) : Control(x, y, width, height) {};
        ListView& setHeaders(std::vector<std::wstring>);
        ListView& addRow(std::vector<std::wstring>);
        ListView& addRow(std::vector<std::string>);
        ListView& clear();

        unsigned int columnSize();
        unsigned int count();

        void create() override;
    };
}