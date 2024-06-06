#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdint>
#include <windows.h>
#include <string>
#include <vector>

namespace lucky {
namespace utils {

	uint64_t GetWeChatWinBase();

    uint64_t GetWeChatBase();

    std::wstring Utf8ToWstring(const std::string& str);

    std::string WstringToUtf8(const std::wstring& str);

    std::wstring AnsiToWstring(const std::string& input, INT64 locale = CP_ACP);

    std::string WstringToAnsi(const std::wstring& input, INT64 locale = CP_ACP);

    std::string WcharToUtf8(wchar_t* wstr);

    std::string StringToHex(const std::string& str);

    std::string HexToString(const std::string& hex_str);

    std::string BytesToHex(const BYTE* bytes, const int length);

    void HexToBytes(const std::string& hex, BYTE* bytes);

    bool IsDigit(const std::string& str);

    std::string Bytes2Hex(const BYTE* bytes, const int length);

    void HideModule(HMODULE module);

    template <typename T1, typename T2>
    std::vector<T1> split(T1 str, T2 letter) {
        std::vector<T1> arr;
        size_t pos;
        while ((pos = str.find_first_of(letter)) != T1::npos) {
            T1 str1 = str.substr(0, pos);
            arr.push_back(str1);
            str = str.substr(pos + 1, str.length() - pos - 1);
        }
        arr.push_back(str);
        return arr;
    }
    uint64_t GetNow();


}  // namespace utils

}  // namespace lucky
#endif