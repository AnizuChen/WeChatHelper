
#ifndef _WECHATH_H_
#define _WECHATH_H_

#include "GetContactResponse.pb.h"
#include <utils/Singleton.h>
#include "AutoHook.h"
#include <functional>
#include "common/WeChatInner.h"

namespace lucky {

	namespace wechat {

		struct WeChat : public utils::Singleton<WeChat> {
			WeChat();
			~WeChat();
			void InstallInitializeProcHook(const std::function<void()>& initializeProc);
			void InstallDeInitializeProcHook(const std::function<void()>& deInitializeProc);
			int8_t InitializeProcHook(uint64_t a1, uint64_t a2);
			int32_t DeInitializeProcHook(uint8_t a1);
			void Start();
			void ShutDown();

			int64_t DelContact(const std::wstring& wxid);
			int64_t GetContact(const std::wstring& wixd, common::Contact& contact);
			int64_t GetContactList(std::vector<common::Contact>& );
			int64_t RemarkContact(const std::wstring& wxid, const std::wstring& remark);
			//opcode=0x3 移出 0xb添加
			int64_t BlackContact(const std::wstring& wxid,uint32_t opcode);

			int64_t DelContactLabel(int32_t labelId);
			//labellist  ,1,2,3,
			int64_t ModifyContactLabel(const std::vector<std::wstring>& wxidList, const std::wstring labelList);

			//消息
			int64_t SendTextMsg(const std::wstring& wxid, const std::wstring& msg, const std::vector<std::wstring>& atList, int type =1);
			int64_t SendImageMsg(const std::wstring& wxid, const std::wstring& fullPath);
			int64_t SendFileMsg(const std::wstring& wxid, const std::wstring& fullPath);

			int64_t SendPatMsg(const std::wstring& roomId, const std::wstring& wxid);
			//发送个人 公众号 名片
			int64_t SendCardMsg(const std::wstring& towxid, const std::wstring& fromwxid);

			//获取群聊信息
			int64_t GetChatRoomDetailInfo(const std::wstring& roomId, common::ChatRoomInfo& info);
			//拉人进群40人以下
			int64_t AddMemberToChatRoom(const std::wstring& roomId, const std::vector<std::wstring>& wxidList);
			//邀请人进群40人以上
			int64_t InviteMemberToChatRoom(const std::wstring& roomId, const std::vector<std::wstring>& wxidList);
			int64_t DelMemberFromChatRoom(const std::wstring& roomId, const std::vector<std::wstring>& wxidList);

			//退出删除群
			int64_t QuitAndDelChatRoom(const std::wstring& roomId);
			//修改群名
			int64_t ModChatRoomTopic(const std::wstring& roomId, const std::wstring& topic);

			//朋友圈点赞
			int64_t SnsObjectLike(const std::string& id, const std::wstring& wxid);

			//朋友圈取消点赞
			int64_t SnsObjectUnLike(const std::string& id);

			//朋友圈评论
			int64_t SnsObjectDoComment(const std::string& id, const std::wstring& comment);

			//朋友圈删除评论
			int64_t SnsObjectDelComment(const std::string& id, uint32_t commentId);

			//CDN下载
			int64_t CDNDownload(const std::string& fileId, const std::string& aeskey, const std::string& md5, const std::string& fileType, const std::string& savePath);

			int64_t GetSelfInfo(common::SelfInfo& out);

		private:
			HookPointPtr			initializeProcHookPoint_;
			std::function<void()>	initializeProc_;
			HookPointPtr			deInitializeProcHookPoint_;
			std::function<void()>	deInitializeProc_;
			std::atomic_bool		initialize_ = false;
			uint64_t				base_ = 0;
		};
	}
}

#endif