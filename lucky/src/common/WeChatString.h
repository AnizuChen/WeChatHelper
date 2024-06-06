#ifndef WECHATSTRING_H
#define WECHATSTRING_H

#include "WeChatString.h"

#include <cstdint>
#include <string>


namespace lucky {
	namespace common {

		struct WeChatWString {

			wchar_t* buf = nullptr;
			int32_t     len = 0;
			int32_t     cap = 0;

			int64_t     c_ptr = 0;
			int32_t     c_len = 0;
			int32_t     c_cap = 0;

			WeChatWString();
			~WeChatWString();

			void Init();

			WeChatWString(const std::wstring& s);
			WeChatWString(const wchar_t* str);

			WeChatWString(const WeChatWString& other);

			WeChatWString(WeChatWString&& other) noexcept;

			WeChatWString& operator=(const WeChatWString& other);
			WeChatWString& operator=(WeChatWString&& other) noexcept;

		

		};

		//union buf[16] 应该就是std::string
		struct WeChatString {

			char* buf = nullptr;
			int64_t		r;
			int64_t		len;
			int64_t     cap; 

			WeChatString();
			~WeChatString();

			void Init();

			WeChatString(const std::string& s);
			WeChatString(const char* str);

			WeChatString(const WeChatString& other);

			WeChatString(WeChatString&& other) noexcept;

			WeChatString& operator=(const WeChatString& other);
			WeChatString& operator=(WeChatString&& other) noexcept;

		};

	}
}

#endif // !WECHATSTRING_H
