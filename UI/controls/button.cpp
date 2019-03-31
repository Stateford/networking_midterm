#include "button.h"

namespace Controls
{
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