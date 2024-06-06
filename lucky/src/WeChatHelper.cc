#include "WeChatHelper.h"
#include <windows.h>
#include "wechat/WeChat.h"

namespace lucky {

	WeChatHelper::WeChatHelper() {
		OutputDebugString("WeChatHelper \n");
	}

	WeChatHelper::~WeChatHelper() {
		OutputDebugString("~WeChatHelper \n");
	}

	void WeChatHelper::Init() {
		bool expected = false;
		bool desired = true;
		if (running_.compare_exchange_strong(expected, desired)) {

			lucky::wechat::WeChat::GetInstance().InstallInitializeProcHook([this]() {
				lucky::service::Service::GetInstance().Start();
				});

			lucky::wechat::WeChat::GetInstance().Start();
		
			lucky::wechat::WeChat::GetInstance().InstallDeInitializeProcHook([this]() {
				OutputDebugString("WeChatHelper DeInitializeProc START \n");
				bool expected = true;
				bool desired = false;
				if (running_.compare_exchange_strong(expected, desired)) {
					lucky::wechat::WeChat::GetInstance().ShutDown();
					lucky::service::Service::GetInstance().ShutDown();
					Sleep(500);
				}
				OutputDebugString("WeChatHelper DeInitializeProc END \n");
			});

		}
	}
	void WeChatHelper::DeInit() {
		OutputDebugString("WeChatHelper DeInit START\n");
		lucky::wechat::WeChat::GetInstance().DeInitializeProcHook(uint8_t(-1));
		OutputDebugString("WeChatHelper DeInit END\n");
	}
	
}