#include "CallBackManager.h"

namespace lucky {

	namespace wechat {

		CallBackManager::CallBackManager() {

		}
		CallBackManager::~CallBackManager() {

		}
		void CallBackManager::Add(uint32_t seqID, std::shared_ptr<CallBack> callback) {
			std::lock_guard<std::mutex> lock(mutex_);
			callback_[seqID] = callback;
		}
		void CallBackManager::Remove(uint32_t seqID) {
			std::lock_guard<std::mutex> lock(mutex_);
			callback_.erase(seqID);
		}
		std::shared_ptr<CallBack> CallBackManager::Get(uint32_t seqID) {
			std::lock_guard<std::mutex> lock(mutex_);
			auto it = callback_.find(seqID);
			if ( it  != callback_.end() ) {
				return it->second;
			}
			return nullptr;
		}
	}
}