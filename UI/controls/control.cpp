#include "../stdafx.h"
#include "control.h"

#include <thread>

namespace Controls
{
    std::vector<Control*> *Control::controls = new std::vector<Control*>();
    unsigned int Control::lastMessageId = 2000;

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