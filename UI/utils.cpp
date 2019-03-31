#include "utils.h"

#include <locale>
#include <codecvt>

namespace Utils
{
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
}