#include "ChatRoomController.h"
#include "utils/Utils.h"
#include <vector>
#include "wechat/NetScene.h"
#include "wechat/WeChat.h"
#include "CreateChatRoomResponse.pb.h"
#include "GetChatroomMemberDetailResponse.pb.h"
#include <google/protobuf/util/json_util.h>
#include <sstream>

namespace lucky {
	namespace service {
		namespace controller {

            using namespace MMPro::micromsg;
            using namespace google::protobuf::util;


            std::string ChatRoomController::NetSceneCreateChatRoom(std::string params) {
                std::vector<std::wstring> wxids = GetArrayParam(params, "$.wxids");
                std::shared_ptr<CreateChatRoomResponse> result = lucky::wechat::NetScence::GetInstance().CreatChatRoom(wxids);
                std::string response = R"({"code":200,"msg":"NetSceneCreateChatRoom."})";
                if (result != nullptr) {
                    response = "";
                    MessageToJsonString(*result.get(), &response);
                }
                return response;
            }

            std::string ChatRoomController::GetChatRoomDetailInfo(std::string params) {
                std::wstring  chatRoomID = GetWStringParam(params, "$.chatroomId");
                common::ChatRoomInfo info;
                lucky::wechat::WeChat().GetChatRoomDetailInfo(chatRoomID, info);
                return info.ToJson();
            }
            std::string ChatRoomController::NetSceneGetMemberFromChatRoom(std::string params) {
                std::wstring  chatRoomID = GetWStringParam(params, "$.chatroomId");
                std::shared_ptr<GetChatroomMemberDetailResponse> result = lucky::wechat::NetScence::GetInstance().GetChatRoomMember(chatRoomID);
                std::string response = R"({"code":200,"msg":"NetSceneGetMemberFromChatRoom."})";
                if (result != nullptr) {
                    response = "";
                    MessageToJsonString(*result.get(), &response);
                }
                return response;
            }
            std::string ChatRoomController::AddMemberToChatRoom(std::string params) {
                std::wstring  chatRoomID = GetWStringParam(params, "$.chatroomId");
                std::vector<std::wstring> wxids = GetArrayParam(params, "$.wxids");
                uint64_t  success = lucky::wechat::WeChat().AddMemberToChatRoom(chatRoomID, wxids);
                std::ostringstream oss;
                oss << "{\"code\":" << success << "}";
                return oss.str();
            }

            std::string ChatRoomController::InviteMemberToChatRoom(std::string params) {
                std::wstring  chatRoomID = GetWStringParam(params, "$.chatroomId");
                std::vector<std::wstring> wxids = GetArrayParam(params, "$.wxids");
                uint64_t  success = lucky::wechat::WeChat().InviteMemberToChatRoom(chatRoomID, wxids);
                std::ostringstream oss;
                oss << "{\"code\":" << success << "}";
                return oss.str();
            }

            std::string ChatRoomController::DelMemberFromChatRoom(std::string params) {
                std::wstring  chatRoomID = GetWStringParam(params, "$.chatroomId");
                std::vector<std::wstring> wxids = GetArrayParam(params, "$.wxids");
                uint64_t  success = lucky::wechat::WeChat().DelMemberFromChatRoom(chatRoomID, wxids);
                std::ostringstream oss;
                oss << "{\"code\":" << success << "}";
                return oss.str();
            }

            std::string ChatRoomController::QuitAndDelChatRoom(std::string params) {
                std::wstring  chatRoomID = GetWStringParam(params, "$.chatroomId");
                uint64_t  success = lucky::wechat::WeChat().QuitAndDelChatRoom(chatRoomID);
                std::ostringstream oss;
                oss << "{\"code\":" << success << "}";
                return oss.str();
            }

          
            std::string ChatRoomController::TopMsg(std::string params) { 
                //2231510
                return "";
            }
            std::string ChatRoomController::CloseTopMsg(std::string params) {
                return "";
            }

            std::string ChatRoomController::ModChatRoomTopic(std::string params) {
                std::wstring  chatRoomID = GetWStringParam(params, "$.chatroomId");
                std::wstring  topic = GetWStringParam(params, "$.topic");
                uint64_t  success = lucky::wechat::WeChat().ModChatRoomTopic(chatRoomID,topic);
                std::ostringstream oss;
                oss << "{\"code\":" << success << "}";
                return oss.str();
            }

            std::string ChatRoomController::ModChatRoomMemberNickName(std::string params) {
              //2225650
                return "";
            }

            std::string ChatRoomController::SetChatRoomAnnouncement(std::string params) {
               //格式化xml比较麻烦后面再实现
                return "";
            }

		}

	}
}