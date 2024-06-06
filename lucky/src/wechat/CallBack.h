#ifndef _CALLBACK_H
#define _CALLBACK_H

#include <memory>
#include <windows.h>

namespace lucky {

	namespace wechat {

		class CallBack : public std::enable_shared_from_this<CallBack> {
			typedef  uint64_t (*__OnNetRespone)(uint64_t a1, int32_t a2, int32_t a3, uint64_t a4, int32_t a5);
		public:
			CallBack();
			~CallBack();
			virtual uint64_t OnNetRespone(uint64_t a1, int32_t a2, int32_t a3, uint64_t a4, int32_t a5);
			uint64_t OnNetResponeHookProxy(uint64_t a1, int32_t a2, int32_t a3, uint64_t a4, int32_t a5);
			void SetSeqID(uint32_t);
			uint32_t GetSeqID();
			void HookOnNetRespone(uint64_t* a2);
			//a2 errType
			//a3 errCode
			//a5 sceneID
			static uint64_t OnNetResponeHook(uint64_t a1, int32_t a2, int32_t a3, uint64_t a4, int32_t a5);
		private:
			uint32_t _seqID = 0;
			__OnNetRespone _OnNetRespone = 0;
		};


		class CallBackAutoTLS {
		public:
			CallBackAutoTLS(const std::shared_ptr<CallBack>&);
			~CallBackAutoTLS();
			static std::shared_ptr<CallBack> GetCallBack();
			static DWORD GetTlsIndex();
			static DWORD tlsIndex;
		};
	}

}


#endif