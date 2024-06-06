#include "MsgController.h"
#include "utils/Utils.h"
#include <vector>
#include "wechat/NetScene.h"
#include "wechat/WeChat.h"
#include "wechat/SyncMgr.h"
#include <google/protobuf/util/json_util.h>
#include <sstream>

namespace lucky {

	namespace service {

		namespace controller {

			std::string MsgController::SendTextMsg(const std::string& message) {
				std::wstring wxid = GetWStringParam(message, "$.wxid");
				std::wstring msg  = GetWStringParam(message, "$.msg");
				std::vector<std::wstring> atlist = GetArrayParam(message, "$.atlist");
				int64_t success = lucky::wechat::WeChat::GetInstance().SendTextMsg(wxid, msg, atlist);
				std::ostringstream oss;
				oss << "{\"code\":" << success << "}";
				return oss.str();
			}

			std::string MsgController::SendImageMsg(const std::string& message) {
				std::wstring wxid = GetWStringParam(message, "$.wxid");
				std::wstring fullPath = GetWStringParam(message, "$.fullPath");
				int64_t success = lucky::wechat::WeChat::GetInstance().SendImageMsg(wxid,fullPath);
				std::ostringstream oss;
				oss << "{\"code\":" << success << "}";
				return oss.str();
			}

			std::string MsgController::SendFileMsg(const std::string& message) {
				std::wstring wxid = GetWStringParam(message, "$.wxid");
				std::wstring fullPath = GetWStringParam(message, "$.fullPath");
				int64_t success = lucky::wechat::WeChat::GetInstance().SendFileMsg(wxid, fullPath);
				std::ostringstream oss;
				oss << "{\"code\":" << success << "}";
				return oss.str();
			}

			std::string MsgController::SendPatMsg(const std::string& message) {
				std::wstring roomId = GetWStringParam(message, "$.roomId");
				std::wstring wxid = GetWStringParam(message, "$.wxid");
				int64_t success = lucky::wechat::WeChat::GetInstance().SendPatMsg(roomId, wxid);
				std::ostringstream oss;
				oss << "{\"code\":" << success << "}";
				return oss.str();
			}

			std::string MsgController::SendCardMsg(const std::string& message) {
				std::wstring towxid = GetWStringParam(message, "$.towxid");
				std::wstring fromwxid = GetWStringParam(message, "$.fromwxid");
				int64_t success = lucky::wechat::WeChat::GetInstance().SendCardMsg(towxid, fromwxid);
				std::ostringstream oss;
				oss << "{\"code\":" << success << "}";
				return oss.str();
			}

			std::string MsgController::SetMessageNotify(const std::string& message) {
				OutputDebugString("SetMessageNotify");
				std::string url = GetStringParam(message, "$.url");
				wechat::SyncMgr::GetInstance().SetMessageNotifyUrl(url);
				std::ostringstream oss;
				oss << "{\"code\":" << 0 << "}";
				return oss.str();
			}

		}
	}
}