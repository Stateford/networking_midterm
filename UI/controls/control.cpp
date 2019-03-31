#include "../stdafx.h"
#include "control.h"

#include <thread>
#include <locale>
#include <codecvt>

namespace Controls
{
    std::vector<Control*> *Control::controls = new std::vector<Control*>();
    unsigned int Control::lastMessageId = 2000;

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

    Control::Control(int x, int y, int width, int height)
    {
        _x = x;
        _y = y;
        _width = width;
        _height = height;
    }

    void Control::callback()
    {
        if (_hasCallBack)
        {
            std::thread([=]()
            {
                _callback();
            }).detach();
        }
    }
}