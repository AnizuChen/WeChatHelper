#ifndef _SYNCMGR_H
#define _SYNCMGR_H

#include "AutoHook.h"
#include "Utils/Singleton.h"
#include <mutex>

namespace lucky {

	namespace wechat {

		class SyncMgr : public utils::Singleton<SyncMgr> {
		public:

			SyncMgr();
			~SyncMgr();

			void InstallDoAddMsgHook();
			void ShutDown();
			uint64_t DoAddMsg(uint64_t, uint64_t, uint64_t);
			void SetMessageNotifyUrl(const std::string& url);

		private:
			HookPointPtr  doAddMsgHookPoint_; //hookPoint
			uint64_t	  base_;
			std::mutex    mutex_;
			std::string   message_notify_url_; 
		};
	}

}


#endif // !_SYNCMGR_H
