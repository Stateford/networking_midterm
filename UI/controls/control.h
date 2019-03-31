#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#include <vector>
#include <functional>
#include <memory>


namespace Controls
{
    std::string utf16_to_utf8(std::wstring);
    std::wstring utf8_to_utf16(std::string);

    class Control
    {
    protected:
        HWND _handle;
        HWND _hwnd;
        bool _hasCallBack = false;
        int _x;
        int _y;
        int _width;
        int _height;
        long _styleMask;
        std::wstring _text = L"";
        static unsigned int lastMessageId;
        unsigned int _parentMessage = 0;
        std::function<void()> _callback;
        
    public:
        static std::vector<Control*> *controls;
        unsigned int index = 0;
        unsigned int messageId;
        
        virtual void callback();

        Control(HWND hwnd) { _hwnd = hwnd; Control::controls->push_back(this); }
        Control(int, int, int, int);

        HWND getHandle() { return _handle; }
        virtual Control& setParentWindow(HWND hwnd) { _hwnd = hwnd; return *this; }
        virtual Control& setStyleMask(long mask) { _styleMask = mask; return *this; }
        virtual Control& setExStyleMask(long mask) {
            SendMessage(_handle, LVM_SETEXTENDEDLISTVIEWSTYLE,
                mask, mask);
            return *this;
        }
        long getStyleMask() { return _styleMask; }
        virtual Control& setText(const wchar_t* text) { _text = text; return *this; };
        virtual Control& setX(int x) { _x = x; return *this; }
        virtual Control& setY(int y) { _y = y; return *this; }
        virtual Control& setPosition(int x, int y)
        {
            _x = x;
            _y = y;
            return *this;
        }
        virtual Control& setParentMessage(unsigned int message) { _parentMessage = message; return *this; }
        virtual unsigned int getParentMessage() { return _parentMessage; }
        virtual Control& setWidth(int width) { _width = width; return *this; }
        virtual Control& setHeight(int height) { _height = height; return *this; }
        virtual Control& setSize(int height, int width)
        {
            _width = width;
            _height = height;
            return *this;
        }
        bool hasCallback() { return _hasCallBack; }
        void registerCallback(const std::function<void()> &lambda) { this->_callback = lambda; _hasCallBack = true; };
        virtual void create() = 0;
    };
}