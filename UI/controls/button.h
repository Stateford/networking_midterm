#pragma once

#include "control.h"

namespace Controls
{
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