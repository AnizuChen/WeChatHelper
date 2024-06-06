#include "NetScene.h"
#include "GetContactResponse.pb.h"
#include "WeChatOffset.h"
#include "WeChatFunction.h"
#include "utils/Utils.h"
#include "CallBack.h"
#include "CallBackManager.h"
#include "NetSceneCallBack.h"
#include "common/WeChatString.h"
#include "MM.h"

namespace lucky {

	namespace wechat {

		using namespace lucky::utils;
		using namespace MMPro::micromsg;


		NetScence::NetScence() {
			timeout_ = std::chrono::milliseconds(3000);
			base_ = GetWeChatWinBase();
		}

		NetScence::~NetScence() {}

		void NetScence::InstallStartTaskHook() {
			OutputDebugString("NetScence::InstallStartTaskHook");
			startTaskHookPoint_ = HookPointPtr(new AutoHookEx<HookModel::BEFORE,
				offset::kSceneCenterStartTask,
				decltype(&NetScence::StartTask)>(base_,
					std::bind(&NetScence::StartTask, this, std::placeholders::_1, std::placeholders::_2),
					HookMethodPtr(new DetoursHook())));
		}

		void NetScence::ShutDown() {
			startTaskHookPoint_.reset();
		}

		int8_t NetScence::StartTask(uint64_t a1, uint64_t* a2) {
			std::shared_ptr<CallBack> callback = CallBackAutoTLS::GetCallBack();
			if (callback == nullptr) { 
				OutputDebugString("StartTask callback == nullptr");
				return 0;
			}
			callback->HookOnNetRespone(a2);
			return 0;
		}

		int64_t NetScence::GetContactRequest(const std::vector<std::wstring>& wxids) {
			function::__NetSceneGetContact NetSceneGetContact = (function::__NetSceneGetContact)(base_ + offset::kNetSceneGetContact);
			function::__Instance instance = (function::__Instance)(base_ + offset::kGetContactMgr);
			std::vector<common::WeChatWString>  strVec;
			for (const auto& wxid : wxids) {
				strVec.emplace_back(common::WeChatWString(wxid));
			}
			common::WeChatWString a3;
			return NetSceneGetContact(instance(), reinterpret_cast<UINT64>(&strVec), reinterpret_cast<UINT64>(&a3));
		}
	
		std::shared_ptr<GetContactResponse> NetScence::GetContact(const std::vector<std::wstring>& wxids) {
			if (wxids.empty()) {return 0;}
			std::shared_ptr<NetSceneCallBack<GetContactResponse>> callback(new NetSceneCallBack<GetContactResponse>());
			CallBackAutoTLS callBackAutoTLS(callback);
			GetContactRequest(wxids);
			return  callback->WaitFor(timeout_);
		}

		int64_t NetScence::SearchContactRequest(const std::wstring& search) {
			common::WeChatWString search_str(search);
			function::__Instance instance = (function::__Instance)(base_ + offset::kSearchContactMgr);
			function::__StartSearchFromScene StartSearchFromScene = (function::__StartSearchFromScene)(base_ + offset::kStartSearchFromScene);
			return StartSearchFromScene(instance(), reinterpret_cast<UINT64>(&search_str));
		}

		std::shared_ptr<SearchContactResponse> NetScence::SearchContact(const std::wstring& search) {
			if (search.empty()) { return 0; }
			std::shared_ptr<NetSceneCallBack<SearchContactResponse>> callback(new NetSceneCallBack<SearchContactResponse>());
			CallBackAutoTLS callBackAutoTLS(callback);
			SearchContactRequest(search);
			return  callback->WaitFor(timeout_);
		}


		int64_t NetScence::VerifyUserRequest(int opcode, const std::wstring& wxid, const std::string& v4, const std::wstring& greet, int scence, int role) {
			
			common::WeChatWString wxidStr(wxid);
			common::WeChatWString greetStr(greet);

			function::__Instance instance = (function::__Instance)(base_ + offset::kGetContactMgr);
			function::__VerifyUser VerifyUser = (function::__VerifyUser)(base_ + offset::kVerifyUser);
			

			common::WeChatString v4Str(v4);
			common::WeChatWString chatroom;

	
			char success = VerifyUser(
				instance(),
				reinterpret_cast<UINT64>(&wxidStr),
				opcode,
				reinterpret_cast<UINT64>(&greetStr),
				scence,
				reinterpret_cast<UINT64>(&v4Str),
				reinterpret_cast<UINT64>(&chatroom),
				role
			);
			return (int64_t)success;
		}

		std::shared_ptr<VerifyUserResponse>  NetScence::VerifyUser(int opcode, const std::wstring& wxid, const std::string& v4, const std::wstring& greet, int scence, int role) {
			//参数校验
			if (wxid.length() == 0) {
				return 0;
			}

			if (opcode == 2 && greet.length() == 0) {
				return 0;
			}

			if (opcode == 3 && v4.length() == 0) {
				return 0;
			}

			std::shared_ptr<NetSceneCallBack<VerifyUserResponse>> callback(new NetSceneCallBack<VerifyUserResponse>());
			CallBackAutoTLS callBackAutoTLS(callback);
			VerifyUserRequest(opcode, wxid,  v4,  greet,  scence,  role);
			return  callback->WaitFor(timeout_);
		}

		std::shared_ptr<VerifyUserResponse>  NetScence::AddContact(const std::wstring& wxid, const std::wstring& greet, int scence, int role) {
			std::shared_ptr<VerifyUserResponse>  verify = VerifyUser(1, wxid, "", L"", scence, 0);
		/*
			if (verify != nullptr && verify ->_baseresponse()._ret() != MMPro::RetConst::MM_OK) {
				OutputDebugString("VerifyUser != MMPro::RetConst::MM_OK");
				return verify;
			} */
			Sleep(500);
			verify = VerifyUser(2, wxid, "", greet, scence, role);
			return  verify;
		}


		std::shared_ptr<VerifyUserResponse>  NetScence::VerifyApply(const std::wstring& wxid, const std::string& v4, int scence, int role) {
			std::shared_ptr<VerifyUserResponse> verify = VerifyUser(3, wxid, v4, L"", scence, role);
			return verify;
		}

		int64_t NetScence::GetContactLabelListRequest() {
			uint64_t get_contact_label_list_addr = base_ + offset::kNetSceneGetContactLabelList;
			function::__NetSceneGetContactLabelList get_contact_label_list =
				(function::__NetSceneGetContactLabelList)get_contact_label_list_addr;
			return get_contact_label_list();

		}
		std::shared_ptr<GetContactLabelListResponse> NetScence::GetContactLabelList() {
			std::shared_ptr<NetSceneCallBack<GetContactLabelListResponse>> callback(new NetSceneCallBack<GetContactLabelListResponse>());
			CallBackAutoTLS callBackAutoTLS(callback);
			GetContactLabelListRequest();
			return  callback->WaitFor(timeout_);
		}


		int64_t NetScence::AddContactLabelRequest(const std::wstring& label) {

			struct ContactLabelIdStruct {
				uint64_t	_0x0 = 00;
				uint64_t	_0x08 = 0;
				wchar_t*	buf = nullptr;
				uint32_t	len = 0;
				uint32_t	cap = 0;
				uint64_t	_0x20 = 0;
				uint64_t	_0x28 = 0;
				uint32_t	_0x30 = 0;
				uint32_t	_0x34 = 0;
			};

			ContactLabelIdStruct st;

			/*
			function::__NewContactLabelIdStruct new_contact_labelId = 
				(function::__NewContactLabelIdStruct)(base_ + offset::kNewContactLabelIdStruct);

			new_contact_labelId(reinterpret_cast<UINT64>(&st)); */

			st.buf = (wchar_t*)label.c_str();
			st.len = static_cast<int32_t>(label.length());
			st.cap = static_cast<int32_t>(label.length());
			st._0x30 = -1;
			st._0x34 = 0;
			st._0x08 = 0x00007FFEFFFFFFFF;

			std::vector<ContactLabelIdStruct> vec;
			vec.emplace_back(st);
			void* NetSceneBaseEx = operator new(0x328);

			function::__NetSceneAddContactLabel NetSceneAddContactLabel = (function::__NetSceneAddContactLabel)(base_ + offset::kNetSceneAddContactLabel);
			uint64_t netbaseEx = NetSceneAddContactLabel(reinterpret_cast<UINT64>(NetSceneBaseEx),1, reinterpret_cast<UINT64>(&vec), -1);

			function::__Instance  instance = (function::__Instance)(base_ + offset::kSceneCenter);
			function::__SceneNetSceneBase SceneNetSceneBase = (function::__SceneNetSceneBase)(base_ + offset::kSceneNetSceneBase);

			return SceneNetSceneBase(instance(), netbaseEx);
		}
		std::shared_ptr<GetContactLabelListResponse>  NetScence::AddContactLabel(const std::wstring& label) {
			std::shared_ptr<NetSceneCallBack<GetContactLabelListResponse>> callback(new NetSceneCallBack<GetContactLabelListResponse>());
			CallBackAutoTLS callBackAutoTLS(callback);
			AddContactLabelRequest(label);
			return  callback->WaitFor(timeout_);
		}

		//这个函数做了防护处理直接在加密入口call
		int64_t NetScence::CreatChatRoomRequest(const std::vector<std::wstring>& wxids) {
			function::__Instance instance = (function::__Instance)(base_ + offset::kChatRoomMgr);
			function::__CreateChatRoom CreateChatRoom = (function::__CreateChatRoom)(base_ + offset::kCreateChatRoom);
			std::vector<common::WeChatWString> wxidVec;
			for (auto it : wxids) {
				wxidVec.emplace_back(common::WeChatWString(std::move(it)));
			}
			CreateChatRoom(instance(), reinterpret_cast<UINT64>(&wxidVec));
			return 0;
		}
		std::shared_ptr<CreateChatRoomResponse> NetScence::CreatChatRoom(const std::vector<std::wstring>& wxids) {
			std::shared_ptr<NetSceneCallBack<CreateChatRoomResponse>> callback(new NetSceneCallBack<CreateChatRoomResponse>());
			CallBackAutoTLS callBackAutoTLS(callback);
			CreatChatRoomRequest(wxids);
			return  callback->WaitFor(timeout_);
		}

		int64_t NetScence::GetChatRoomMemberRequest(const std::wstring& roomId) {
			common::WeChatWString roomIdStr(roomId);
			function::__GetChatroomMemberDetail GetChatroomMemberDetail = (function::__GetChatroomMemberDetail)(base_ + offset::kGetChatroomMemberDetail);
			return GetChatroomMemberDetail(reinterpret_cast<UINT64>(roomIdStr.buf), reinterpret_cast<UINT64>(&roomIdStr),0);
		}
		std::shared_ptr<GetChatroomMemberDetailResponse> NetScence::GetChatRoomMember(const std::wstring& roomId) {
			std::shared_ptr<NetSceneCallBack<GetChatroomMemberDetailResponse>> callback(new NetSceneCallBack<GetChatroomMemberDetailResponse>());
			CallBackAutoTLS callBackAutoTLS(callback);
			GetChatRoomMemberRequest(roomId);
			return  callback->WaitFor(timeout_);
		}

		int64_t NetScence::GetA8KeyRequest(const std::wstring& url, const std::wstring& wxid, uint32_t nScene, uint32_t codeType, uint32_t codeVersion ) {
			/**
			__int64 __fastcall sub_1824ABD40(
				__int64 a1,                             // netscene分配内存
				__int64 a2,                             // url
				int a3,                                 // nscene 公众号链接=0 扫码=0x25(37d) 群邀请链接0x1
				unsigned int a4,                        // 公众号链接=8d 扫码=0
				int a5,                                 // 自增计数
				__int64 a6,                             // 无用参数
				__int64 a7,                             // 聊天对象
				int a8,                                 // codeType = 公众号=0 扫码=0x13(19)  
				int a9)                                 // CodeVersion 公众号=0 扫码=0x6 收款码=0x5
			*/
			function::__GetA8Key GetA8Key = (function::__GetA8Key)(base_ + offset::kGetA8Key);
			void* NetSceneBaseEx = operator new(0x420);
			common::WeChatWString urlStr(url);
			common::WeChatWString wxidStr(wxid);
			int a5 = 0; //扫码应该自增这个
			uint64_t netbaseEx = GetA8Key(
				reinterpret_cast<UINT64>(NetSceneBaseEx),
				reinterpret_cast<UINT64>(&urlStr),
				nScene,
				0,
				a5,
				0,
				reinterpret_cast<UINT64>(&wxidStr),
				codeType,
				codeVersion
			);
			function::__Instance  scene_center = (function::__Instance)(base_ + offset::kSceneCenter);
			function::__SceneNetSceneBase scene_net_scene_base = (function::__SceneNetSceneBase)(base_ + offset::kSceneNetSceneBase);
			return scene_net_scene_base(scene_center(), netbaseEx);
		}
		std::shared_ptr<GetA8KeyResp> NetScence::GetA8Key(const std::wstring& url, const std::wstring& wxid, uint32_t nScene, uint32_t codeType, uint32_t codeVersion) {
			std::shared_ptr<NetSceneCallBack<GetA8KeyResp>> callback(new NetSceneCallBack<GetA8KeyResp>());
			CallBackAutoTLS callBackAutoTLS(callback);
			GetA8KeyRequest(url, wxid, nScene, codeType, codeVersion);
			return  callback->WaitFor(timeout_);
		}


		//获取朋友圈首页
		int64_t NetScence::TimelineGetFirstPageRequest() {
			function::__Instance  instance = (function::__Instance)(base_ + offset::kSnsTimeLineMgr);
			function::__TimelineGetFirstPage TimelineGetFirstPage = (function::__TimelineGetFirstPage)(base_ + offset::kTimelineGetFirstPage);
			return TimelineGetFirstPage(instance(),1);
		}
		std::shared_ptr<SnsTimeLineResponse> NetScence::TimelineGetFirstPage() {
			std::shared_ptr<NetSceneCallBack<SnsTimeLineResponse>> callback(new NetSceneCallBack<SnsTimeLineResponse>());
			CallBackAutoTLS callBackAutoTLS(callback);
			TimelineGetFirstPageRequest();
			return  callback->WaitFor(timeout_);
		}

		//获取朋友圈下一页
		int64_t NetScence::TimelineGetNextPageRequest(const std::string& id) {
			OutputDebugString(id.c_str());
			function::__Instance  instance = (function::__Instance)(base_ + offset::kSnsTimeLineMgr);
			function::__TimelineGetNextPage TimelineGetNextPage = (function::__TimelineGetNextPage)(base_ + offset::kTimelineGetNextPage);
			return TimelineGetNextPage(instance(), std::stoull(id));
		}
		std::shared_ptr<SnsTimeLineResponse> NetScence::TimelineGetNextPage(const std::string& id) {
			std::shared_ptr<NetSceneCallBack<SnsTimeLineResponse>> callback(new NetSceneCallBack<SnsTimeLineResponse>());
			CallBackAutoTLS callBackAutoTLS(callback);
			TimelineGetNextPageRequest(id);
			return  callback->WaitFor(timeout_);
		}

		int64_t NetScence::SnsObjectDetailRequest(const std::string& id) {
			function::__Instance  instance = (function::__Instance)(base_ + offset::kSnsTimeLineMgr);
			function::__SnsObjectDetail SnsObjectDetail = (function::__TimelineGetNextPage)(base_ + offset::kSnsObjectDetail);
			return SnsObjectDetail(instance(), std::stoull(id));
		}
		std::shared_ptr<SnsObjectDetailResponse> NetScence::SnsObjectDetail(const std::string& id) {
			std::shared_ptr<NetSceneCallBack<SnsObjectDetailResponse>> callback(new NetSceneCallBack<SnsObjectDetailResponse>());
			CallBackAutoTLS callBackAutoTLS(callback);
			SnsObjectDetailRequest(id);
			return  callback->WaitFor(timeout_);
		}


	}
	
}



