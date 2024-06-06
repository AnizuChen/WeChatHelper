

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


			//opcode 1 У�� 2 ��� 3 ͨ������
			int64_t VerifyUserRequest(int opcode, const std::wstring& wxid, const std::string& v4, const std::wstring& greet, int scence, int role);
			std::shared_ptr<VerifyUserResponse> VerifyUser(int opcode, const std::wstring& wxid, const std::string& v4, const std::wstring& greet, int scence, int role);


			//role ����Ȩ��	0 = ���졢����Ȧ��΢���˶��� 1 = �������������� 2 = ������������ 3 = �������������� + ������������ 8 = ������
		    //scence 1=����QQ�� 2=���� 3=΢�ź� 6=������� 10��13=ͨѶ¼ 12=QQ���� 14=Ⱥ��  15=�ֻ���  17=��Ƭ  30=ɨһɨ  31=facebook
			std::shared_ptr<VerifyUserResponse>  AddContact(const std::wstring& wxid, const std::wstring& greet, int scence, int role);
			//ͨ����������
			std::shared_ptr<VerifyUserResponse>  VerifyApply(const std::wstring& wxid,const std::string& v4, int scence, int role);
		
			//��ȡ���ѱ�ǩ
			int64_t GetContactLabelListRequest();
			std::shared_ptr<GetContactLabelListResponse>  GetContactLabelList();

			//��Ӻ��ѱ�ǩ
			int64_t AddContactLabelRequest(const std::wstring& label);
			std::shared_ptr<GetContactLabelListResponse>  AddContactLabel(const std::wstring& label);

			//����Ⱥ��
			int64_t CreatChatRoomRequest(const std::vector<std::wstring>& wxids);
			std::shared_ptr<CreateChatRoomResponse> CreatChatRoom(const std::vector<std::wstring>& wxids);


			//��ȡȺ��Ա
			int64_t GetChatRoomMemberRequest(const std::wstring& roomId);
			std::shared_ptr<GetChatroomMemberDetailResponse> GetChatRoomMember(const std::wstring& roomId);

			//��ȡA8KEY
			int64_t GetA8KeyRequest(const std::wstring& url, const std::wstring& wxid, uint32_t nScene, uint32_t codeType, uint32_t codeVersion);
			std::shared_ptr<GetA8KeyResp> GetA8Key(const std::wstring& url, const std::wstring& wxid, uint32_t nScene, uint32_t codeType = 0x13, uint32_t codeVersion = 0x6);

			//��ȡ����Ȧ��ҳ
			int64_t TimelineGetFirstPageRequest();
			std::shared_ptr<SnsTimeLineResponse> TimelineGetFirstPage();

			//��ȡ����Ȧ��һҳ (��һҳ���һ��ID)
			int64_t TimelineGetNextPageRequest(const std::string& id);
			std::shared_ptr<SnsTimeLineResponse> TimelineGetNextPage(const std::string& id);

			//��ȡĳ������Ȧ����
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