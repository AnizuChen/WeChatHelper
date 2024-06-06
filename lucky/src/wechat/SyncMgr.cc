#include "SyncMgr.h"
#include "utils/Utils.h"
#include "common/Work.h"
#include "common/ThreadPool.h"
#include "WeChatOffset.h"
#include "service/HttpClient.h"
#include <sstream>
#include "AddMsg.pb.h"
#include <google/protobuf/util/json_util.h>

namespace lucky {
	namespace wechat {

		using namespace MMPro::micromsg;

		struct NotifyWork : public common::Work {
			NotifyWork(const std::string& url, std::string&& message) :
				url(url), message(std::move(message)) {
			}
			~NotifyWork() {

			}
			void Run() {
				service::HttpClient client(url);
				client.SendRequest(message);
			}
			std::string  url;
			std::string message;
		};


		SyncMgr::SyncMgr():base_(0) {
			base_ = utils::GetWeChatWinBase();
		}
		SyncMgr::~SyncMgr() {

		}
		void SyncMgr::InstallDoAddMsgHook() {
			OutputDebugString("SyncMgr::InstallDoAddMsgHook");
			doAddMsgHookPoint_ = HookPointPtr(new AutoHookEx<HookModel::BEFORE,
				offset::kDoAddMsg,
				decltype(&SyncMgr::DoAddMsg)>(base_,
					std::bind(&SyncMgr::DoAddMsg, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
					HookMethodPtr(new DetoursHook())));
		}
		void SyncMgr::ShutDown() {
			this->doAddMsgHookPoint_.reset();
		}
		uint64_t SyncMgr::DoAddMsg(uint64_t a1, uint64_t a2, uint64_t a3) {
			unsigned int result = *(unsigned int*)(a2 + 0x10);
			std::stringstream s1;
			s1 << "SyncMgr::DoAddMsg result: " << result;
			OutputDebugString(s1.str().c_str());
			if (result == 5) {
				AddMsg addMsg;
				uint64_t v20 = *(uint64_t *)(a2 + 8);
				uint64_t* v21 = *(uint64_t**)(v20 + 8);
				if (v21[3] >= 0x10)
					v21 = (uint64_t*)*v21;
				addMsg.ParseFromArray((void*)v21, *(unsigned int*)(v20 + 0x10));
				std::string message;
				google::protobuf::util::MessageToJsonString(addMsg, &message);
				//OutputDebugString(message.c_str());
				std::lock_guard<std::mutex> lock(mutex_);
				if (!this->message_notify_url_.empty()) {
					common::ThreadPool::GetInstance().Submit(new NotifyWork(this->message_notify_url_,std::move( message)));
				}
			}
			return 0;
		}

		void SyncMgr::SetMessageNotifyUrl(const std::string& url) {
			std::lock_guard<std::mutex> lock(mutex_);
			this->message_notify_url_ = url;
		}
	}
}