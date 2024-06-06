

#ifndef _NETSCENE_H_
#define _NETSCENE_H_

#include <windows.h>
#include <string>
#include <vector>
#include <future>
#include <map>
#include <mutex>
#include <string>
#include <chrono>

#include "utils/Singleton.h"
#include "AutoHook.h"

#include "GetContactResponse.pb.h"
#include "SearchContactResponse.pb.h"
#include "VerifyUserResponse.pb.h"
#include "GetContactLabelListResponse.pb.h"
#include "CreateChatRoomResponse.pb.h"
#include "GetChatroomMemberDetailResponse.pb.h"
#include "GetA8KeyResp.pb.h"
#include "SnsTimeLineResponse.pb.h"
#include "SnsObjectDetailResponse.pb.h"

namespace lucky {

	namespace wechat {

		using namespace MMPro::micromsg;
		using lucky::utils::Singleton;

		class NetScence : public Singleton<NetScence> {
		public:
			NetScence();
			~NetScence();

			int64_t GetContactRequest(const std::vector<std::wstring>& wxids);
			std::shared_ptr<GetContactResponse> GetContact(const std::vector<std::wstring>& wxids);
			
			int64_t SearchContactRequest(const std::wstring& search);
			std::shared_ptr<SearchContactResponse> SearchContact(const std::wstring& search);


			//opcode 1 校验 2 添加 3 通过好友
			int64_t VerifyUserRequest(int opcode, const std::wstring& wxid, const std::string& v4, const std::wstring& greet, int scence, int role);
			std::shared_ptr<VerifyUserResponse> VerifyUser(int opcode, const std::wstring& wxid, const std::string& v4, const std::wstring& greet, int scence, int role);


			//role 朋友权限	0 = 聊天、朋友圈、微信运动等 1 = 不让他（她）看 2 = 不看他（她） 3 = 不让他（她）看 + 不看他（她） 8 = 仅聊天
		    //scence 1=搜索QQ号 2=邮箱 3=微信号 6=单向添加 10和13=通讯录 12=QQ好友 14=群聊  15=手机号  17=名片  30=扫一扫  31=facebook
			std::shared_ptr<VerifyUserResponse>  AddContact(const std::wstring& wxid, const std::wstring& greet, int scence, int role);
			//通过好友申请
			std::shared_ptr<VerifyUserResponse>  VerifyApply(const std::wstring& wxid,const std::string& v4, int scence, int role);
		
			//获取好友标签
			int64_t GetContactLabelListRequest();
			std::shared_ptr<GetContactLabelListResponse>  GetContactLabelList();

			//添加好友标签
			int64_t AddContactLabelRequest(const std::wstring& label);
			std::shared_ptr<GetContactLabelListResponse>  AddContactLabel(const std::wstring& label);

			//创建群聊
			int64_t CreatChatRoomRequest(const std::vector<std::wstring>& wxids);
			std::shared_ptr<CreateChatRoomResponse> CreatChatRoom(const std::vector<std::wstring>& wxids);


			//获取群成员
			int64_t GetChatRoomMemberRequest(const std::wstring& roomId);
			std::shared_ptr<GetChatroomMemberDetailResponse> GetChatRoomMember(const std::wstring& roomId);

			//获取A8KEY
			int64_t GetA8KeyRequest(const std::wstring& url, const std::wstring& wxid, uint32_t nScene, uint32_t codeType, uint32_t codeVersion);
			std::shared_ptr<GetA8KeyResp> GetA8Key(const std::wstring& url, const std::wstring& wxid, uint32_t nScene, uint32_t codeType = 0x13, uint32_t codeVersion = 0x6);

			//获取朋友圈首页
			int64_t TimelineGetFirstPageRequest();
			std::shared_ptr<SnsTimeLineResponse> TimelineGetFirstPage();

			//获取朋友圈下一页 (上一页最后一个ID)
			int64_t TimelineGetNextPageRequest(const std::string& id);
			std::shared_ptr<SnsTimeLineResponse> TimelineGetNextPage(const std::string& id);

			//获取某条朋友圈详情
			int64_t SnsObjectDetailRequest(const std::string& id);
			std::shared_ptr<SnsObjectDetailResponse> SnsObjectDetail(const std::string& id);
			

		public:
			void InstallStartTaskHook();
			void ShutDown();
			int8_t StartTask(uint64_t, uint64_t*);
		private:
			HookPointPtr  startTaskHookPoint_; //hookPoint
			std::chrono::milliseconds timeout_;
			uint64_t base_;
		};
	}
}

#endif