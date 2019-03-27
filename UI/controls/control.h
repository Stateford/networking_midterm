#pragma once

#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#include <vector>
#include <functional>


namespace Controls
{
    class Control
    {
    protected:
        HWND _handle;
        HWND _hwnd;

        int _x;
        int _y;
        int _width;
        int _height;
        long _styleMask;
        std::wstring _text;
        static unsigned int lastMessageId;
    public:
        unsigned int messageId;

        std::function<void()> callback;
        Control(HWND hwnd) { _hwnd = hwnd; }
        Control(int, int, int, int);
        HWND getHandle() { return _handle; }
        virtual Control& setParentWindow(HWND hwnd) { _hwnd = hwnd; return *this; }
        virtual Control& setStyleMask(long mask) { _styleMask = mask; return *this; }
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
        virtual Control& setWidth(int width) { _width = width; return *this; }
        virtual Control& setHeight(int height) { _height = height; return *this; }
        virtual Control& setSize(int height, int width)
        {
            _width = width;
            _height = height;
            return *this;
        }
        void registerCallback(const std::function<void()> &lambda) { this->callback = lambda; };
        virtual void create() = 0;
    };

    // LISTVIEW
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
        ListView& clear();

        unsigned int columnSize();
        unsigned int count();

        void create() override;
    };

    // BUTTON CLASS
    class Button : public Control
    {
    private:
        const wchar_t* _type = WC_BUTTON;
    public:
        Button(HWND hwnd) : Control(hwnd) {};
        Button(int x, int y, int width, int height) : Control(x, y, width, height) {};

        void create() override;
    };
}