#ifndef _CALLBACKMANAGER_H
#define _CALLBACKMANAGER_H


#include <mutex>
#include <memory>
#include <map>
#include "CallBack.h"
#include <cstdint>
#include <utils/Singleton.h>

namespace lucky {

	namespace wechat {

		using lucky::utils::Singleton;

		class CallBackManager : public Singleton<CallBackManager> {
		public:
			CallBackManager();
			~CallBackManager();
			void Remove(uint32_t);
			void Add(uint32_t, std::shared_ptr<CallBack> );
			std::shared_ptr<CallBack> Get(uint32_t seqID);
		private:
			std::mutex mutex_;
			std::map<uint32_t, std::shared_ptr<CallBack> > callback_;
		};

	}
}

#endif