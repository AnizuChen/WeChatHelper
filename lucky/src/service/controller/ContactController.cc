#include "ContactController.h"
#include "utils/Utils.h"
#include <vector>
#include "wechat/NetScene.h"
#include "GetContactResponse.pb.h"
#include "SearchContactResponse.pb.h"
#include "VerifyUserResponse.pb.h"
#include "wechat/WeChat.h"
#include <google/protobuf/util/json_util.h>
#include <sstream>

using namespace MMPro::micromsg;
using namespace google::protobuf::util;

namespace lucky {

	namespace service {

		namespace controller {

			std::string ContactController::NetSceneGetContact(const std::string& message) {
				std::vector<std::wstring> wxids = GetArrayParam(message, "$.wxids");
				std::shared_ptr<GetContactResponse> result  = lucky::wechat::NetScence::GetInstance().GetContact(wxids);
				std::string response = R"({"code":200,"msg":"NetSceneGetContact."})";
				if (result != nullptr) {
					response = "";
					MessageToJsonString(*result.get(), &response);
				}
				return response;
			}

			std::string ContactController::NetSceneSearchContact(const std::string& message) {
				std::wstring search = GetWStringParam(message, "$.search");
				std::shared_ptr<SearchContactResponse> result = lucky::wechat::NetScence::GetInstance().SearchContact(search);
				std::string response = R"({"code":200,"msg":"NetSceneSearchContact."})";
				if (result != nullptr) {
					response = "";
					MessageToJsonString(*result.get(), &response);
				}
				return response;
			}

			std::string ContactController::NetSceneAddContact(const std::string& params) {
				std::wstring wxid = GetWStringParam(params, "$.wxid"); //wxid or v3
				std::wstring greet = GetWStringParam(params, "$.greet");
				int scence = GetIntParam(params, "$.scence");
				int role = GetIntParam(params, "$.role");
				std::shared_ptr<VerifyUserResponse> result = lucky::wechat::NetScence::GetInstance().AddContact(wxid, greet, scence, role);
				std::string response = R"({"code":200,"msg":"AddContact."})";
				if (result != nullptr) {
					response = "";
					MessageToJsonString(*result.get(), &response);
				}
				return response;
			}

			std::string ContactController::NetSceneVerifyApply(const std::string& params) {
				std::wstring wxid = GetWStringParam(params, "$.wxid"); //wxid or v3
				std::string v4 = GetStringParam(params, "$.v4");  //v4
				int scence = GetIntParam(params, "$.scence");
				int role = GetIntParam(params, "$.role");
				std::shared_ptr<VerifyUserResponse> result = lucky::wechat::NetScence::GetInstance().VerifyApply(wxid, v4, scence, role);
				std::string response = R"({"code":200,"msg":"NetSceneVerifyApply."})";
				if (result != nullptr) {
					response = "";
					MessageToJsonString(*result.get(), &response);
				}
				return response;
			}

			std::string ContactController::NetSceneGetContactLabelList(const std::string& params) {
				std::shared_ptr<GetContactLabelListResponse> result = lucky::wechat::NetScence::GetInstance().GetContactLabelList();
				std::string response = R"({"code":200,"msg":"NetGetContactLabelList."})";
				if (result != nullptr) {
					response = "";
					MessageToJsonString(*result.get(), &response);
				}
				return response;
			}

			std::string ContactController::NetSceneAddContactLabel(const std::string& params) {
				std::wstring label = GetWStringParam(params, "$.label");
				std::shared_ptr<GetContactLabelListResponse> result = lucky::wechat::NetScence::GetInstance().AddContactLabel(label);
				std::string response = R"({"code":200,"msg":"NetSceneAddContactLabel."})";
				if (result != nullptr) {
					response = "";
					MessageToJsonString(*result.get(), &response);
				}
				return response;
			}

			std::string ContactController::DelContact(const std::string& params) {
				std::wstring wxid = GetWStringParam(params, "$.wxid");
				int64_t success = lucky::wechat::WeChat::GetInstance().DelContact(wxid);
				std::ostringstream oss;
				oss << "{\"code\":" << success << "}";
				return oss.str();
			}

			std::string ContactController::GetContact(const std::string& params) {
				OutputDebugString("ContactController::GetContact");
				std::wstring wxid = GetWStringParam(params, "$.wxid");
				common::Contact contact;
				int64_t success = lucky::wechat::WeChat::GetInstance().GetContact(wxid, contact);
				return contact.ToJson();
			}

			std::string ContactController::GetContactList(const std::string& params) {
				std::vector<common::Contact> contactList;
				int64_t success = lucky::wechat::WeChat::GetInstance().GetContactList(contactList);
				std::stringstream ss;
				ss << "[";

				for (auto it = contactList.begin(); it != contactList.end(); ++it) {
					ss << it->ToJson();
					if (std::next(it) != contactList.end()) {
						ss << ",";
					}
				}
				ss << "]";
				return ss.str();
			}

			std::string ContactController::RemarkContact(const std::string& params) {
				std::wstring wxid = GetWStringParam(params, "$.wxid");
				std::wstring remark = GetWStringParam(params, "$.remark");
				int64_t success = lucky::wechat::WeChat::GetInstance().RemarkContact(wxid, remark);
				std::ostringstream oss;
				oss << "{\"code\":" << success << "}";
				return oss.str();
			}

			std::string ContactController::BlackContact(const std::string& params) {
				std::wstring wxid = GetWStringParam(params, "$.wxid");
				uint32_t opcode = GetIntParam(params, "$.opcode");
				int64_t success = lucky::wechat::WeChat::GetInstance().BlackContact(wxid, opcode);
				std::ostringstream oss;
				oss << "{\"code\":" << success << "}";
				return oss.str();
			}

			std::string ContactController::DelContactLabel(const std::string& params) {
				int32_t labelId = GetIntParam(params, "$.labelId");
				int64_t success = lucky::wechat::WeChat::GetInstance().DelContactLabel(labelId);
				std::ostringstream oss;
				oss << "{\"code\":" << success << "}";
				return oss.str();
			}

			std::string ContactController::ModifyContactLabel(const std::string& params) {
				std::vector<std::wstring> wxidList = GetArrayParam(params, "$.wxidList");
				std::wstring labelList = GetWStringParam(params, "$.labelList");
				int64_t success = lucky::wechat::WeChat::GetInstance().ModifyContactLabel(wxidList, labelList);
				std::ostringstream oss;
				oss << "{\"code\":" << success << "}";
				return oss.str();
			}
		}
	}
}