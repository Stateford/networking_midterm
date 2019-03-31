#pragma once

#include <string>

namespace Utils
{
    std::string utf16_to_utf8(std::wstring);
    std::wstring utf8_to_utf16(std::string);
}