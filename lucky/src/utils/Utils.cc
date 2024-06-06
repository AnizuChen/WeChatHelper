
#include "Utils.h"
#include <windows.h>
#include <string>
#include <vector>
#include <winternl.h>
#include <sstream>

namespace lucky {
namespace utils {

	uint64_t GetWeChatWinBase() {
		return (uint64_t)GetModuleHandleA("WeChatWin.dll");
	}

    uint64_t GetWeChatBase() {
        return (uint64_t)GetModuleHandleA("WeChat.exe");
    }
   
    const std::string hex_table = "0123456789abcdef";

    std::wstring Utf8ToWstring(const std::string& str) {
        return AnsiToWstring(str, CP_UTF8);
    }

    std::string WstringToUtf8(const std::wstring& str) {
        return WstringToAnsi(str, CP_UTF8);
    }

    std::wstring AnsiToWstring(const std::string& input, INT64 locale) {
        int wchar_len = MultiByteToWideChar(locale, 0, input.c_str(), -1, NULL, 0);
        if (wchar_len > 0) {
            std::vector<wchar_t> temp(wchar_len);
            MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, &temp[0], wchar_len);
            return std::wstring(&temp[0]);
        }
        return std::wstring();
    }

    std::string WstringToAnsi(const std::wstring& input, INT64 locale) {
        int char_len = WideCharToMultiByte(locale, 0, input.c_str(), -1, 0, 0, 0, 0);
        if (char_len > 0) {
            std::vector<char> temp(char_len);
            WideCharToMultiByte(locale, 0, input.c_str(), -1, &temp[0], char_len, 0, 0);
            return std::string(&temp[0]);
        }
        return std::string();
    }

    std::string WcharToUtf8(wchar_t* wstr) {
        int c_size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, FALSE);
        if (c_size > 0) {
            char* buffer = new char[c_size];
            WideCharToMultiByte(CP_UTF8, 0, wstr, -1, buffer, c_size, NULL, FALSE);
            std::string str(buffer);
            delete[] buffer;
            buffer = NULL;
            return str;
        }
        return std::string();
    }

    std::string StringToHex(const std::string& str) {
        std::string sb;
        for (int i = 0; i < str.length(); i++) {
            sb += hex_table.at((str[i] & 0xf0) >> 4);
            sb += hex_table.at((str[i] & 0x0f) >> 0);
        }
        return sb;
    }

    std::string HexToString(const std::string& hex_str) {
        std::string ret;
        for (int i = 0; i < hex_str.length(); i += 2) {
            ret += BYTE(hex_table.find(hex_str.at(i)) << 4 |
                hex_table.find(hex_str.at(UINT64(i) + 1)));
        }
        return ret;
    }

    std::string BytesToHex(const BYTE* bytes, const int length) {
        if (bytes == NULL) {
            return "";
        }
        std::string buff;
        const int len = length;
        for (int j = 0; j < len; j++) {
            int high = bytes[j] / 16, low = bytes[j] % 16;
            buff += (high < 10) ? ('0' + high) : ('a' + high - 10);
            buff += (low < 10) ? ('0' + low) : ('a' + low - 10);
        }
        return buff;
    }
    void HexToBytes(const std::string& hex, BYTE* bytes) {
        int byte_len = hex.length() / 2;
        std::string str;
        unsigned int n;
        for (int i = 0; i < byte_len; i++) {
            str = hex.substr(UINT64(i) * 2, 2);
            sscanf_s(str.c_str(), "%x", &n);
            bytes[i] = n;
        }
    }

    void HideModule(HMODULE module) {

        PPEB peb = (PPEB)__readgsqword(0x60);
        PPEB_LDR_DATA ldr = peb->Ldr;

        void* cur_ptr = *((void**)((unsigned char*)ldr + 0x18));
        void* next_ptr = cur_ptr;
        do {
            void* next = *((void**)((unsigned char*)next_ptr));
            void* last = *((void**)((unsigned char*)next_ptr + 0x8));
            void* base_addr = *((void**)((unsigned char*)next_ptr + 0x30));
            if (base_addr == module) {
                *((void**)((unsigned char*)last)) = next;
                *((void**)((unsigned char*)next + 0x8)) = last;
                cur_ptr = next;
            }
            next_ptr = *((void**)next_ptr);
        } while (cur_ptr != next_ptr);
    }

    bool IsDigit(const std::string& str) {
        if (str.length() == 0) {
            return false;
        }
        for (auto it : str) {
            if (it < '0' || it > '9') {
                return false;
            }
        }
        return true;
    }

std::string Bytes2Hex(const BYTE* bytes, const int length) {
    if (bytes == NULL) {
        return "";
    }
    std::string buff;
    const int len = length;
    for (int j = 0; j < len; j++) {
        int high = bytes[j] / 16, low = bytes[j] % 16;
        buff += (high < 10) ? ('0' + high) : ('a' + high - 10);
        buff += (low < 10) ? ('0' + low) : ('a' + low - 10);
    }
    return buff;
}

bool IsTextUtf8(const char* str, INT64 length) {
    char endian = 1;
    bool littlen_endian = (*(char*)&endian == 1);

    size_t i;
    int bytes_num;
    unsigned char chr;

    i = 0;
    bytes_num = 0;
    while (i < length) {
        if (littlen_endian) {
            chr = *(str + i);
        }
        else {  // Big Endian
            chr = (*(str + i) << 8) | *(str + i + 1);
            i++;
        }

        if (bytes_num == 0) {
            if ((chr & 0x80) != 0) {
                while ((chr & 0x80) != 0) {
                    chr <<= 1;
                    bytes_num++;
                }
                if ((bytes_num < 2) || (bytes_num > 6)) {
                    return false;
                }
                bytes_num--;
            }
        }
        else {
            if ((chr & 0xC0) != 0x80) {
                return false;
            }
            bytes_num--;
        }
        i++;
    }
    return (bytes_num == 0);
}


std::string Wstring2String(std::wstring wstr)
{
    // support chinese
    std::string res;
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), nullptr, 0, nullptr, nullptr);
    if (len <= 0) {
        return res;
    }
    char* buffer = new char[(size_t)len + 1];
    if (buffer == nullptr) {
        return res;
    }
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, nullptr, nullptr);
    buffer[len] = '\0';
    res.append(buffer);
    delete[] buffer;
    return res;
}

std::wstring String2Wstring(std::string wstr)
{
    std::wstring res;
    int len = MultiByteToWideChar(CP_ACP, 0, wstr.c_str(), wstr.size(), nullptr, 0);
    if (len < 0) {
        return res;
    }
    wchar_t* buffer = new wchar_t[(size_t)len + 1];
    if (buffer == nullptr) {
        return res;
    }
    MultiByteToWideChar(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len);
    buffer[len] = '\0';
    res.append(buffer);
    delete[] buffer;
    return res;
}

uint64_t GetNow() {

    SYSTEMTIME sysTime;
    GetSystemTime(&sysTime);

    FILETIME fileTime;
    SystemTimeToFileTime(&sysTime, &fileTime);

    ULARGE_INTEGER uli;
    uli.LowPart = fileTime.dwLowDateTime;
    uli.HighPart = fileTime.dwHighDateTime;

    ULONGLONG timestamp = uli.QuadPart / 10000000ULL - 11644473600ULL;
    return timestamp;
}

}  // namespace utils
}  // namespace lucky
