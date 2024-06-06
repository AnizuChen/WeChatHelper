
#ifndef _WECHATHELPER_H_
#define _WECHATHELPER_H_

#include <Windows.h>
#include "service/Service.h"
#include "utils/Singleton.h"

namespace lucky {

	struct WeChatHelper : public utils::Singleton<WeChatHelper> {
		WeChatHelper();
		~WeChatHelper();
		void Init();
		void DeInit();
	private:
		std::atomic_bool running_ = {false};
	};

}

#endif