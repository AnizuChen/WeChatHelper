
#include <string>
#include "WeChatString.h"
#include <sstream>
#include <windows.h>

namespace lucky {

	namespace common {


			WeChatWString::WeChatWString() {
				std::stringstream ss;
				ss << "WeChatWString::WeChatWString " << std::hex << ":" << this;
				OutputDebugString(ss.str().c_str());
			}

			void WeChatWString::Init() {
				buf = nullptr;
				len = 0;
				cap = 0;
				c_ptr = 0;
				c_len = 0;
				c_cap = 0;
			}

			WeChatWString::~WeChatWString() {

				std::stringstream ss;
				ss << "WeChatWString::~WeChatWString " << std::hex << ":" << this << ":" << buf;
				OutputDebugString(ss.str().c_str());
				
				if (buf != nullptr) {
					delete[] buf;
					buf = nullptr;
					len = 0;
					cap = 0;
				}
				if (c_ptr) {
					delete[](void*)c_ptr;
					c_ptr = 0;
					c_len = 0;
					c_cap = 0;
				}
			}

			WeChatWString::WeChatWString(const std::wstring& s) {

				std::stringstream ss;
				ss << "WeChatWString::WeChatWString const std::wstring " << std::hex << ":" << this;
				OutputDebugString(ss.str().c_str());

				Init();
				if (!s.empty()) {
					buf = new wchar_t[s.length() + 1];
					wcscpy_s(buf, (s.length() + 1), s.c_str());
					len = static_cast<int32_t>(s.length());
					cap = static_cast<int32_t>(s.length());
					c_ptr = 0;
					c_len = 0;
					c_cap = 0;
				}
			}

			WeChatWString::WeChatWString(const wchar_t* str) {
				std::stringstream ss;
				ss << "WeChatWString::WeChatWString const wchar_t " << std::hex << ":" << this;
				OutputDebugString(ss.str().c_str());
				Init();
				if (wcslen(str) > 0) {
					buf = new wchar_t[wcslen(str) + 1];
					wcscpy_s(buf, (wcslen(str) + 1), str);
					len = static_cast<int32_t>(wcslen(str));
					cap = static_cast<int32_t>(wcslen(str));
					c_ptr = 0;
					c_len = 0;
					c_cap = 0;
				}
			}

			WeChatWString::WeChatWString(const WeChatWString& other) {
				std::stringstream ss;
				ss << "WeChatWString::WeChatWString WeChatWString " << std::hex << ":" << this;
				OutputDebugString(ss.str().c_str());
				Init();
				if (other.len > 0) {
					buf = new wchar_t[size_t(other.len) + 1];
					wcscpy_s(buf, uint64_t(other.len) + 1, other.buf);
					len = other.len;
					cap = other.cap;
					c_ptr = other.c_ptr;
					c_len = other.c_len;
					c_cap = other.c_cap;
				}
			}


			WeChatWString::WeChatWString(WeChatWString&& other) noexcept :
				buf(other.buf), len(other.len), cap(other.cap),
				c_ptr(other.c_ptr), c_len(other.c_ptr), c_cap(other.c_cap) {
				std::stringstream ss;
				ss << "WeChatWString::WeChatWString WeChatWString&& " << std::hex << ":" << this  << ":" << &other;
				OutputDebugString(ss.str().c_str());
				ss.clear();
				ss << "WeChatWString::WeChatWString WeChatWString&& " << std::hex << buf << ":" << len;
				OutputDebugString(ss.str().c_str());
				other.buf = nullptr;
				other.len = 0;
				other.cap = 0;
				other.c_ptr = 0;
				other.c_len = 0;
				other.c_cap = 0;
			}

			WeChatWString& WeChatWString::operator=(const WeChatWString& other) {
				std::stringstream ss;
				ss << "WeChatWString::WeChatWString operator=& " << std::hex << ":" << this;
				OutputDebugString(ss.str().c_str());
				if (this == &other) {
					return *this;
				}
				Init();
				if (other.len > 0) {
					buf = new wchar_t[sizeof(other.len) + 1];
					wcscpy_s(buf, uint64_t(other.len) + 1, other.buf);
					len = other.len;
					cap = other.cap;
					c_ptr = other.c_ptr;
					c_len = other.c_len;
					c_cap = other.c_cap;
				}
				return *this;
			}

			WeChatWString& WeChatWString::operator=(WeChatWString&& other) noexcept {
				std::stringstream ss;
				ss << "WeChatWString::WeChatWString operator=&& " << std::hex << ":" << this;
				OutputDebugString(ss.str().c_str());
				if (this == &other) {
					return *this;
				}
				if (buf != nullptr) {
					delete[] buf;
				}
				if (c_ptr) {
					delete[](void*)c_ptr;
				}
				buf = other.buf;
				len = other.len;
				cap = other.cap;
				c_ptr = other.c_ptr;
				c_len = other.c_len;
				c_cap = other.c_cap;

				other.buf = nullptr;
				other.len = 0;
				other.cap = 0;
				other.c_ptr = 0;
				other.c_len = 0;
				other.c_cap = 0;
				return *this;
			}




			WeChatString::WeChatString():buf(nullptr), r(0),len(0),cap(0) {}

			WeChatString::~WeChatString() {

				std::stringstream ss;
				ss << "WeChatString::~WeChatString :" << std::hex << (void*)buf << ":" << this;
				OutputDebugString(ss.str().c_str());
				buf = nullptr;
				len = 0;
				cap = 0;
				r = 0;
			}

			void WeChatString::Init() {
				buf = nullptr;
				len = 0;
				cap = 0;
				r = 0;
			}

			WeChatString::WeChatString(const std::string& s) {

				Init();
				if (!s.empty()) {
					buf = (char*)s.data();
					len = s.length();
					cap = s.length() + 1;
					r = 0;
					
				}
			}

			WeChatString::WeChatString(const char* str) {
				std::stringstream ss;
				ss << "WeChatString::WeChatString  const char:" << std::hex << (void*)buf << ":" << this;
				OutputDebugString(ss.str().c_str());
				Init(); 
				if (strlen(str) > 0) {
					buf = (char*)str;
					len = strlen(str);
					cap = len + 1;
					r = 0;
				}
			}

			WeChatString::WeChatString(const WeChatString& other) {
				std::stringstream ss;
				ss << "WeChatString::WeChatString  const WeChatString:" << std::hex << (void*)buf << ":" << this;
				OutputDebugString(ss.str().c_str());
				Init();
				if (other.len > 0) {
					buf = other.buf;
					len = other.len;
					cap = other.cap;
					r = other.r;
				}
			}


			WeChatString::WeChatString(WeChatString&& other) noexcept :
				buf(other.buf), len(other.len), cap(other.cap),
				r(other.r) {
				std::stringstream ss;
				ss << "WeChatString::WeChatString  WeChatString&&:" << std::hex << (void*)buf << ":" << this;
				OutputDebugString(ss.str().c_str());
				other.buf = nullptr;
				other.len = 0;
				other.cap = 0;
				other.r = 0;
			}


			WeChatString& WeChatString::operator=(const WeChatString& other) {
				std::stringstream ss;
				ss << "WeChatString::WeChatString  operator=:" << std::hex << (void*)buf << ":" << this;
				OutputDebugString(ss.str().c_str());
				if (this == &other) {
					return *this;
				}
				Init();
				if (other.len > 0) {
					buf = other.buf;
					len = other.len;
					cap = other.cap;
					r = other.r;
				}
				return *this;
			}

			WeChatString& WeChatString::operator=(WeChatString&& other) noexcept {
				std::stringstream ss;
				ss << "WeChatString::WeChatString  operator=&&:" << std::hex << (void*)buf << ":" << this;
				OutputDebugString(ss.str().c_str());
				if (this == &other) {
					return *this;
				}
				buf = other.buf;
				len = other.len;
				cap = other.cap;
				r = other.r;
				other.buf = nullptr;
				other.len = 0;
				other.cap = 0;
				other.r = 0;
				return *this;
			}

	}
}

