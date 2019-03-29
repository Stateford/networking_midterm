#include "../stdafx.h"
#include "control.h"

#include <locale>
#include <codecvt>

namespace Controls
{
    std::vector<Control*> *Control::controls = new std::vector<Control*>();

    std::string utf16_to_utf8(std::wstring utf16)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::string temp = converter.to_bytes(utf16);
        return temp;
    }

    std::wstring utf8_to_utf16(std::string utf8)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring temp = converter.from_bytes(utf8);
        return temp;
    }

    unsigned int Control::lastMessageId = 2000;

    Control::Control(int x, int y, int width, int height)
    {
        _x = x;
        _y = y;
        _width = width;
        _height = height;
    }

    void ListView::create()
    {
        _handle = CreateWindow(
            _type,  // Predefined class; Unicode assumed 
            L"",      // Button text 
            _styleMask,  // Styles 
            _x,         // x position 
            _y,         // y position 
            _width,        // Button width
            _height,        // Button height
            _hwnd,     // Parent window
            (HMENU)Control::lastMessageId,       // No menu.
            (HINSTANCE)GetWindowLong(_hwnd, GWL_HINSTANCE),
            NULL);      // Pointer not needed.

        messageId = Control::lastMessageId;
        Control::lastMessageId++;
    }

    unsigned int ListView::count()
    {
        unsigned int count = SendMessage(_handle, LVM_GETITEMCOUNT, 0, 0);
        return count;
    }

    unsigned int ListView::columnSize()
    {
        HWND hWndHdr = (HWND)SendMessage(_handle, LVM_GETHEADER, 0, 0);
        unsigned int count = (int)SendMessage(hWndHdr, HDM_GETITEMCOUNT, 0, 0);
        return count;
    }

    ListView& ListView::setHeaders(std::vector<std::wstring> headers)
    {
        _headers = headers;
        LVCOLUMN lvc{ 0 };
        lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH | LVCF_FMT;
        lvc.fmt = LVCFMT_LEFT;
        for (unsigned int i = 0; i < _headers.size(); i++)
        {
            lvc.iSubItem = i;
            lvc.cx = 100;
            lvc.pszText = &_headers[i][0];
            ListView_InsertColumn(_handle, i, &lvc);
        }
        return *this;
    }

    ListView& ListView::clear()
    {
        ListView_DeleteAllItems(_handle);
        return *this;
    }

    ListView& ListView::addRow(std::vector<std::wstring> row)
    {
        if (row.size() > this->columnSize())
            throw std::exception("Too many items added to row");

        unsigned int count = this->count();
        LVITEM item{ 0 };
        item.iItem = count;
        item.mask = LVIF_TEXT;
        item.pszText = (LPWSTR)L"test";
        ListView_InsertItem(_handle, &item);

        for (unsigned int i = 0; i < _headers.size(); i++)
            ListView_SetItemText(_handle, count, i, &row[i][0]);

        return *this;
    }

    ListView& ListView::addRow(std::vector<std::string> row)
    {
        std::vector<std::wstring> utf18Vector;
        for (auto &p : row)
        {
            std::wstring convertedStr = utf8_to_utf16(p);
            utf18Vector.push_back(convertedStr);
        }
        return addRow(utf18Vector);
    }

    void Button::create()
    {
        _handle = CreateWindow(
            _type,  // Predefined class; Unicode assumed 
            _text.c_str(),      // Button text 
            _styleMask,  // Styles 
            _x,         // x position 
            _y,         // y position 
            _width,        // Button width
            _height,        // Button height
            _hwnd,     // Parent window
            (HMENU)Control::lastMessageId,       // No menu.
            (HINSTANCE)GetWindowLong(_hwnd, GWL_HINSTANCE),
            NULL);      // Pointer not needed.

        messageId = Control::lastMessageId;
        Control::lastMessageId++;
    }
}