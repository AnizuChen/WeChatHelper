#include "WeChat.h"
#include "AutoHook.h"
#include "WeChatOffset.h"
#include "WeChatFunction.h"
#include "utils/Utils.h"
#include "NetScene.h"
#include "SyncMgr.h"
#include "VTableHook.h"
#include "common/WeChatString.h"
#include <sstream>

namespace lucky {
	
	namespace wechat {


		WeChat::WeChat() {
			base_ = utils::GetWeChatWinBase();
		}

		WeChat::~WeChat() {
			OutputDebugString("~WeChat()\n");
		}

		void WeChat::InstallInitializeProcHook(const std::function<void()>& initializeProc) {
			OutputDebugString("InstallInitializeProcHook()\n");
			initializeProc_ = initializeProc;
			//这里选取一个LOOP函数里面的调用进行HOOK
			initializeProcHookPoint_ = HookPointPtr(new AutoHookEx<HookModel::AFTER,
				offset::kMessageLoop,
				decltype(&WeChat::InitializeProcHook)>(base_,
					std::bind(&WeChat::InitializeProcHook, this, std::placeholders::_1, std::placeholders::_2),
					HookMethodPtr(new DetoursHook())));
		}

		void  WeChat::InstallDeInitializeProcHook(const std::function<void()>& deInitializeProc) {
			OutputDebugString("InstallDeInitializeProcHook()\n");
			deInitializeProc_ = deInitializeProc;
			//HOOK WM_DESTROY 
			deInitializeProcHookPoint_ = HookPointPtr(new AutoHookEx<HookModel::BEFORE,
				offset::kWMDestroy,
				decltype(&WeChat::DeInitializeProcHook)>(base_,
					std::bind(&WeChat::DeInitializeProcHook, this, std::placeholders::_1),
					HookMethodPtr(new DetoursHook())));
		}

		int8_t WeChat::InitializeProcHook(uint64_t a,uint64_t b) {
			OutputDebugString("HOOK InitializeProcHook ENTER \n");
			bool expected = false;
			bool desired = true;
			if (initialize_.compare_exchange_strong(expected, desired)) {
				OutputDebugString("HOOK InitializeProcHook Start Initialize_\n");
				initializeProc_();
				OutputDebugString("HOOK InitializeProcHook RESET START\n");
				initializeProcHookPoint_.reset(); //初始化之后恢复(一定是AFTER模式才行)
				OutputDebugString("HOOK InitializeProcHook RESET END\n"); 
			}
			OutputDebugString("HOOK InitializeProcHook RET\n");
			return 0;
		}

		int32_t WeChat::DeInitializeProcHook(uint8_t a1) {
			OutputDebugString("WM_DESTROY HOOK DeInitializeProcHook ENTER \n");
			bool exit = false;
			if (a1 != uint8_t(-1)) {
				CONTEXT context;
				context.ContextFlags = CONTEXT_INTEGER;
				GetThreadContext(GetCurrentThread(), &context);
				int msg  = (int)context.R14; //WM_DESTORY
				if (msg == 2) {  
					exit = true;
				}
			}
			else {
				//主动退出
				exit = true;
			}
			if (!exit) {
				return 0;
			}
			bool expected = true;
			bool desired = false;
			if (initialize_.compare_exchange_strong(expected, desired)) {
				VTableHook::GetInstance().ShutDown();
				OutputDebugString("WM_DESTROY HOOK DeInitializeProcHook Start\n");
				deInitializeProc_();
				OutputDebugString("WM_DESTROY HOOK DeInitializeProcHook END\n");
			}
			OutputDebugString("WM_DESTROY HOOK DeInitializeProcHook RET\n");
			return true;
		}

		void WeChat::Start() {
			NetScence::GetInstance().InstallStartTaskHook();
			SyncMgr::GetInstance().InstallDoAddMsgHook();
		}
		void WeChat::ShutDown() {
			NetScence::GetInstance().ShutDown();
			SyncMgr::GetInstance().ShutDown();
		}

		int64_t WeChat::DelContact(const std::wstring& wxid) {
			char success = -1;
			common::WeChatWString to_del(wxid);
			function::__Instance instance = (function::__Instance)(base_ + offset::kGetContactMgr);
			function::__DelContact DelContact = (function::__DelContact)(base_ + offset::kDelContact);
			success = DelContact(instance(), reinterpret_cast<UINT64>(&to_del));
			return (int64_t)success;
		}

		int64_t WeChat::GetContact(const std::wstring& wxid, common::Contact& contact) {
			common::WeChatWString toUser(wxid);
			int64_t success = -1;
			function::__Constructor Constructor = (function::__Constructor)(base_ + offset::kNewContact);
			function::__Instance instance = (function::__Instance)(base_ + offset::kGetContactMgr);
			function::__GetContact GetContact = (function::__GetContact)(base_ + offset::kGetContact);
			char buff[0x6B0] = { 0 };
			UINT64 contactBuf = Constructor(reinterpret_cast<UINT64>(&buff));
			success = GetContact(instance(), reinterpret_cast<UINT64>(&toUser), contactBuf);
			common::ContactCast contactcast = *(common::ContactCast*)contactBuf;
			contactcast.Cast(contact);
			/*
			free_contact(contact);  //ContactCast vptr -> free_contact
			*/
			return success;
		}

		int64_t WeChat::GetContactList(std::vector<common::Contact>& contactList) {
			int64_t success = -1;
			function::__Instance instance = (function::__Instance)(base_ + offset::kGetContactMgr);
			function::__GetContactList GetContactList = (function::__GetContactList)(base_ + offset::kGetContactList);
			std::vector<common::ContactCast> contactVec;
			success = GetContactList(instance(), reinterpret_cast<uint64_t>(&contactVec));
			for (auto it : contactVec) {
				common::Contact contact;
				it.Cast(contact);
				contactList.emplace_back(contact);
			}
			return success;
		}

		int64_t WeChat::RemarkContact(const std::wstring& wxid, const std::wstring& remark) {
			int64_t success = -1;
			function::__RemarkContact RemarkContact = (function::__RemarkContact)(base_ + offset::kRemarkContact);
			common::WeChatWString toUser(wxid);
			common::WeChatWString remarkStr(remark);
			success = RemarkContact(
				reinterpret_cast<uint64_t>(remarkStr.buf), 
				reinterpret_cast<uint64_t>(&toUser),
				reinterpret_cast<uint64_t>(&remarkStr));
			return success;
		}

		int64_t WeChat::BlackContact(const std::wstring& wxid, uint32_t opcode) {
			int64_t success = -1;
			function::__BlackContact BlackContact = (function::__BlackContact)(base_ + offset::kBlackContact);
			common::WeChatWString toUser(wxid);
			success = BlackContact(
				reinterpret_cast<uint64_t>(toUser.buf),
				reinterpret_cast<uint64_t>(&toUser),
				opcode);
			return success;
		}

		int64_t WeChat::DelContactLabel(int32_t labelId) {
			std::vector<int32_t> vec;
			vec.emplace_back(labelId);
			void* NetSceneBaseEx = operator new(0x320);
			function::__DelContactLabel DelContactLabel =
				(function::__DelContactLabel)(base_ + offset::kNetSceneDelContactLabel);
			uint64_t netbaseEx = DelContactLabel(reinterpret_cast<UINT64>(NetSceneBaseEx), reinterpret_cast<UINT64>(&vec));
			function::__Instance  instance = (function::__Instance)(base_ + offset::kSceneCenter);
			function::__SceneNetSceneBase SceneNetSceneBase = (function::__SceneNetSceneBase)(base_ + offset::kSceneNetSceneBase);
			return SceneNetSceneBase(instance(), netbaseEx);
		}

		int64_t WeChat::ModifyContactLabel(const std::vector<std::wstring>& wxidList, const std::wstring labelList) {
			struct ContactLabelIdStruct {
				uint64_t	_0x0 = 00;
				wchar_t*     buf = nullptr;
				uint32_t	 len = 0;
				uint32_t	 cap = 0;
				uint64_t	_0x18 = 0;
				uint64_t	_0x20 = 0;
				wchar_t*	c_buf = nullptr;
				uint32_t	c_len = 0;
				uint32_t	c_cap = 0;
				uint64_t    _0x38 = 0;
				uint64_t    _0x40 = 0;

			};
	
			std::vector<ContactLabelIdStruct> vec;
			
			for (auto it : wxidList) {
				ContactLabelIdStruct st;
				st.buf = (wchar_t*)it.c_str();
				st.len = static_cast<int32_t>(it.length());
				st.cap = static_cast<int32_t>(it.length());
				st.c_buf = (wchar_t*)labelList.c_str();
				st.c_len = static_cast<int32_t>(labelList.length());
				st.c_cap = static_cast<int32_t>(labelList.length());
				vec.emplace_back(st);
			}

			void* NetSceneBaseEx = operator new(0x308);
			function::__ModifyContactLabel mod_contact_label =
				(function::__ModifyContactLabel)(base_ + offset::kNetSceneModifyContactLabel);
			uint64_t netbaseEx = mod_contact_label(reinterpret_cast<UINT64>(NetSceneBaseEx), reinterpret_cast<UINT64>(&vec));
			function::__Instance  instance = (function::__Instance)(base_ + offset::kSceneCenter);
			function::__SceneNetSceneBase SceneNetSceneBase = (function::__SceneNetSceneBase)(base_ + offset::kSceneNetSceneBase);
			return SceneNetSceneBase(instance(), netbaseEx);
		}

		int64_t WeChat::SendTextMsg(const std::wstring& wxid, const std::wstring& msg, const std::vector<std::wstring>& at, int type) {
			uint8_t ChatMsg[0x490] = {0};
			common::WeChatWString toUser(wxid);
			common::WeChatWString msgStr(msg);
			std::vector<common::WeChatWString> atList;
			for (auto it : at) {
				atList.emplace_back(common::WeChatWString(std::move(it)));
			}
			function::__SendTextMsg SendTextMsg = (function::__SendTextMsg)(base_ + offset::kSendTextMsg);
			function::__Destructor Destructor = (function::__Destructor)(base_ + offset::kFreeChatMsg);
			uint64_t success = SendTextMsg(reinterpret_cast<uint64_t>(&ChatMsg),
				reinterpret_cast<uint64_t>(&toUser),
				reinterpret_cast<uint64_t>(&msgStr),
				reinterpret_cast<uint64_t>(&atList), type, 1, 0, 0);
			Destructor(reinterpret_cast<uint64_t>(&ChatMsg));
			return success;
		}

		int64_t WeChat::SendImageMsg(const std::wstring& wxid, const std::wstring& fullPath) {
			
			uint8_t ChatMsg[0x490];
			common::WeChatWString toUser(wxid);
			common::WeChatWString msgStr(fullPath);
			function::__Instance instance = (function::__Instance)(base_ + offset::kSendMessageMgr);
			function::__SendImageMsg SendImageMsg = (function::__SendImageMsg)(base_ + offset::kSendImageMsg);
			function::__Constructor Constructor = (function::__Constructor)(base_ + offset::kNewChatMsg);
			function::__Destructor Destructor = (function::__Destructor)(base_ + offset::kFreeChatMsg);
			
			uint64_t ChatMsgPtr = Constructor(reinterpret_cast<uint64_t>(&ChatMsg));

			uint8_t ChatMsg2[0x490];
			uint64_t ChatMsg2Ptr =
				Constructor(reinterpret_cast<uint64_t>(&ChatMsg2));
			uint64_t temp1 = 0;
			uint64_t temp2 = 0;
			uint64_t temp3 = 1;
			uint64_t* flag[10] = {};
			flag[0] = reinterpret_cast<uint64_t*>(temp3);
			flag[8] = &temp1;
			flag[9] = &temp2;
			flag[1] = reinterpret_cast<uint64_t*>(ChatMsg2);

			uint64_t success = SendImageMsg(
				instance(),
				ChatMsgPtr,
				reinterpret_cast<uint64_t>(&toUser),
				reinterpret_cast<uint64_t>(&msgStr),
				reinterpret_cast<uint64_t>(&flag)
			);
			Destructor(ChatMsgPtr);
			Destructor(ChatMsg2Ptr);
			return success;
		}


		int64_t WeChat::SendFileMsg(const std::wstring& wxid, const std::wstring& fullPath) {

			uint8_t ChatMsg[0x490];

			common::WeChatWString toUser(wxid);
			common::WeChatWString msgStr(fullPath);

			common::WeChatWString a;
			common::WeChatWString b;
			common::WeChatWString c;

			function::__Instance instance = (function::__Instance)(base_ + offset::kAppMsgMgr);
			function::__SendFile SendFile = (function::__SendFile)(base_ + offset::kSendFileMsg);
			function::__Constructor Constructor = (function::__Constructor)(base_ + offset::kNewChatMsg);
			function::__Destructor Destructor = (function::__Destructor)(base_ + offset::kFreeChatMsg);
			uint64_t ChatMsgPtr = Constructor(reinterpret_cast<uint64_t>(&ChatMsg));
			int64_t success = SendFile(instance(), ChatMsgPtr,
				reinterpret_cast<uint64_t>(&toUser),
				reinterpret_cast<uint64_t>(&msgStr), 1,
				reinterpret_cast<uint64_t>(&a), 0,
				reinterpret_cast<uint64_t>(&b), 0,
				reinterpret_cast<uint64_t>(&c), 0, 0xC);
			Destructor(ChatMsgPtr);
			return success;
		}


		int64_t WeChat::SendPatMsg(const std::wstring& roomId, const std::wstring& wxid) {
			common::WeChatWString roomIdStr(roomId);
			common::WeChatWString wxidStr(wxid);
			function::__SendPatMsg SendPatMsg = (function::__SendPatMsg)(base_ + offset::kSendPatMsg);
			return SendPatMsg(reinterpret_cast<uint64_t>(&roomIdStr), reinterpret_cast<uint64_t>(&wxidStr),0);
		}

		int64_t WeChat::SendCardMsg(const std::wstring& towxid, const std::wstring& fromwxid) {
			common::WeChatWString toUser(fromwxid);
			int64_t success = -1;
			function::__Constructor Constructor = (function::__Constructor)(base_ + offset::kNewContact);
			function::__Destructor Destructor = (function::__Destructor)(base_ + offset::kFreeContact);
			function::__Instance instance = (function::__Instance)(base_ + offset::kGetContactMgr);
			function::__GetContact GetContact = (function::__GetContact)(base_ + offset::kGetContact);
			char buff[0x6B0] = { 0 };
			UINT64 contactBuf = Constructor(reinterpret_cast<UINT64>(&buff));
			success = GetContact(instance(), reinterpret_cast<UINT64>(&toUser), contactBuf);
			function::__GetContactCardContent get_contact_card_content =
				(function::__GetContactCardContent)(base_ + offset::kGetContactCardContent);
			common::WeChatWString cardContet;
			get_contact_card_content(reinterpret_cast<UINT64>(&cardContet), contactBuf);
			std::vector<std::wstring> vec;
			success = SendTextMsg(towxid, std::wstring(cardContet.buf, cardContet.len), vec, 0x2A);
			Destructor(contactBuf);
			return success;
		}

		int64_t WeChat::GetChatRoomDetailInfo(const std::wstring& roomId, common::ChatRoomInfo& info) {
			common::WeChatWString roomIdStr(roomId);
			uint8_t success = -1;
			function::__Instance  instance = (function::__Instance)(base_ + offset::kChatRoomMgr);
			function::__Constructor constructor = (function::__Constructor)(base_ + offset::kChatRoomInfoConstructor);
			function::__GetChatRoomDetailInfo  GetChatRoomDetailInfo = (function::__GetChatRoomDetailInfo)(base_ + offset::kGetChatRoomDetailInfo);
			char buff[0x148] = { 0 };
			UINT64 chatRoomInfoBuf = constructor(reinterpret_cast<UINT64>(&buff));
			success = GetChatRoomDetailInfo(instance(), reinterpret_cast<UINT64>(&roomIdStr), chatRoomInfoBuf, 1);
			common::ChatRoomInfoCast cast = *(common::ChatRoomInfoCast*)chatRoomInfoBuf;
			cast.Cast(info);
			return success;
		}

		int64_t WeChat::AddMemberToChatRoom(const std::wstring& roomId, const std::vector<std::wstring>& wxidList) {
			function::__Instance  instance = (function::__Instance)(base_ + offset::kChatRoomMgr);
			function::__DoAddMemberToChatRoom  DoAddMemberToChatRoom = (function::__DoAddMemberToChatRoom)(base_ + offset::kDoAddMemberToChatRoom);
			std::vector<common::WeChatWString> vec;
			for (auto it : wxidList) {
				vec.emplace_back(common::WeChatWString(std::move(it)));
			}
			uint64_t r[2] = { 0,0 };
			common::WeChatWString roomIdStr(roomId);
			return DoAddMemberToChatRoom(instance(), reinterpret_cast<UINT64>(&vec), 
				reinterpret_cast<UINT64>(&roomIdStr), reinterpret_cast<UINT64>(&r));
		}

		int64_t WeChat::InviteMemberToChatRoom(const std::wstring& roomId, const std::vector<std::wstring>& wxidList) {
			function::__Instance  instance = (function::__Instance)(base_ + offset::kChatRoomMgr);
			function::__InviteMemberToChatRoom  InviteMemberToChatRoom = (function::__InviteMemberToChatRoom)(base_ + offset::kInviteMemberToChatRoom);
			std::vector<common::WeChatWString> vec;
			for (auto it : wxidList) {
				vec.emplace_back(common::WeChatWString(std::move(it)));
			}
			uint64_t r[2] = { 0,0 };
			common::WeChatWString roomIdStr(roomId);
			return InviteMemberToChatRoom(instance(), reinterpret_cast<UINT64>(&vec),
				reinterpret_cast<UINT64>(&roomIdStr), reinterpret_cast<UINT64>(&r));
		}

		int64_t WeChat::DelMemberFromChatRoom(const std::wstring& roomId, const std::vector<std::wstring>& wxidList) {
			function::__Instance  instance = (function::__Instance)(base_ + offset::kChatRoomMgr);
			function::__DoDelMemberFromChatRoom  DoDelMemberFromChatRoom = (function::__DoDelMemberFromChatRoom)(base_ + offset::kDoDelMemberFromChatRoom);
			std::vector<common::WeChatWString> vec;
			for (auto it : wxidList) {
				vec.emplace_back(common::WeChatWString(std::move(it)));
			}
			common::WeChatWString roomIdStr(roomId);
			return DoDelMemberFromChatRoom(instance(), reinterpret_cast<UINT64>(&vec),
				reinterpret_cast<UINT64>(&roomIdStr));
		}

		int64_t WeChat::QuitAndDelChatRoom(const std::wstring& roomId) {
			function::__Instance  instance = (function::__Instance)(base_ + offset::kChatRoomMgr);
			function::__QuitAndDelChatRoom  QuitAndDelChatRoom = (function::__QuitAndDelChatRoom)(base_ + offset::kQuitAndDelChatRoom);
			common::WeChatWString roomIdStr(roomId);
			return QuitAndDelChatRoom(instance(), reinterpret_cast<UINT64>(&roomIdStr), 0);
		}

		int64_t WeChat::ModChatRoomTopic(const std::wstring& roomId, const std::wstring& topic) {
			function::__Instance  instance = (function::__Instance)(base_ + offset::kOpLogMgr);
			function::__ModChatRoomTopic  ModChatRoomTopic = (function::__ModChatRoomTopic)(base_ + offset::kModChatRoomTopic);
			common::WeChatWString roomIdStr(roomId);
			common::WeChatWString topicStr(topic);
			return ModChatRoomTopic(instance(), reinterpret_cast<UINT64>(&roomIdStr), reinterpret_cast<UINT64>(&topic));
		}

		int64_t WeChat::SnsObjectLike(const std::string& id, const std::wstring& wxid) {
			//这个实现逻辑在comment里面...
			struct CommentReq {
				uint64_t id = 0;
				uint64_t _0x8 = 0x0000004D00000000;
				common::WeChatWString wxid;
				char buf[0x138] = { 0 };
			};
			CommentReq req;
			req.id = std::stoull(id);
			req.wxid = common::WeChatWString(wxid);

			uint32_t now = utils::GetNow();

			char* p = (char*)&req;
			*(int32_t*)(p + 0x54) = 1;
			*(int32_t*)(p + 0x78) = now; //时间戳
			*(int64_t*)(p + 0x120) = now; //时间戳

			char b[0x624] = { 0 };
			common::WeChatWString c;
			function::__SnsObjectLike  SnsObjectLike = (function::__SnsObjectLike)(base_ + offset::kSnsObjectLike);
			void* NetSceneBaseEx = operator new(0x440);
			int64_t netbaseEx = SnsObjectLike(reinterpret_cast<UINT64>(NetSceneBaseEx), reinterpret_cast<UINT64>(&req), reinterpret_cast<UINT64>(b), reinterpret_cast<UINT64>(&c));
			function::__Instance  scene_center = (function::__Instance)(base_ + offset::kSceneCenter);
			function::__SceneNetSceneBase scene_net_scene_base = (function::__SceneNetSceneBase)(base_ + offset::kSceneNetSceneBase);
			return scene_net_scene_base(scene_center(), netbaseEx);
		}


		int64_t WeChat::SnsObjectUnLike(const std::string& id) {
			function::__SnsObjectOp  SnsObjectOp = (function::__SnsObjectOp)(base_ + offset::kSnsObjectOp);
			void* NetSceneBaseEx = operator new(0x338);
			int64_t netbaseEx = SnsObjectOp(
				reinterpret_cast<UINT64>(NetSceneBaseEx), 
				std::stoull(id),
				5,
				0,
				0
			);
			function::__Instance  scene_center = (function::__Instance)(base_ + offset::kSceneCenter);
			function::__SceneNetSceneBase scene_net_scene_base = (function::__SceneNetSceneBase)(base_ + offset::kSceneNetSceneBase);
			return scene_net_scene_base(scene_center(), netbaseEx);
		}

		int64_t WeChat::SnsObjectDoComment(const std::string& id, const std::wstring& comment) {
			function::__SnsObjectDoComment  SnsObjectDoComment = (function::__SnsObjectDoComment)(base_ + offset::kSnsObjectDoComment);
			common::WeChatWString commentStr(comment);
			common::WeChatWString b;
			SnsObjectDoComment(
				std::stoull(id),
				reinterpret_cast<UINT64>(&commentStr),
				0,
				0,
				reinterpret_cast<UINT64>(&b)
			);
			return 0;
		}

		int64_t WeChat::SnsObjectDelComment(const std::string& id, uint32_t commentId) {
			function::__SnsObjectOp  SnsObjectOp = (function::__SnsObjectOp)(base_ + offset::kSnsObjectOp);
			void* NetSceneBaseEx = operator new(0x338);
			int64_t netbaseEx = SnsObjectOp(
				reinterpret_cast<UINT64>(NetSceneBaseEx),
				std::stoull(id),
				4,
				commentId,
				0
			);
			function::__Instance  scene_center = (function::__Instance)(base_ + offset::kSceneCenter);
			function::__SceneNetSceneBase scene_net_scene_base = (function::__SceneNetSceneBase)(base_ + offset::kSceneNetSceneBase);
			return scene_net_scene_base(scene_center(), netbaseEx);
		}

		int64_t WeChat::CDNDownload(const std::string& fileId, 
			const std::string& aeskey, const std::string& msgId,
			const std::string& fileType, const std::string& savePath) {
			//图片下载
			struct CDNDownload {
				char buf[0x58] = { 0 };
				std::string msgIdStr; //0x58+0x20
				std::string fileIdStr; //0x78+0x20
				std::string aeskeyStr;	//0x98+0x20
				std::string savePathStr; //0xB8+0x20
				char _buf[0x4B0] = { 0 };
			};
			
			CDNDownload cdnDownload;
			char* a2 = (char*)&cdnDownload;
			((int64_t(*)(int64_t))(base_ + 0x21BC600))(reinterpret_cast<int64_t>(a2));

			
			cdnDownload.msgIdStr = msgId;
			cdnDownload.fileIdStr = fileId;
			cdnDownload.aeskeyStr = aeskey;
			cdnDownload.savePathStr = savePath;

			//*(int32_t*)(a2 + 0xD8) = 2;  //1代表啥 2 3 0x13 (1 原图 2 缩略)
			*(int32_t*)(a2 + 0xD8) = 1;
			*(int32_t*)(a2 + 0xDC) = 1;
			*(int32_t*)(a2 + 0xE0) = 1;
			*(uint8_t*)(a2 + 0xE4) = 1;
			*(int32_t*)(a2 + 0x118) = 1;
			*(int32_t*)(a2 + 0x178) = 1;
		//	*(int32_t*)(a2 + 0x1A8) = 1;  //0 1 1缩略 0 原图
			*(int32_t*)(a2 + 0x1A8) = 0;  //0代表啥 
			*(int32_t*)(a2 + 0x1E0) = 1;
			//*(int8_t*)(a2 + 0x331) = 1;
			*(int8_t*)(a2 + 0x331) = 0;
			*(int32_t*)(a2 + 0x334) = 2; //WxAM decoder
			*(uint64_t*)(a2 + 0x520) = base_ + 0x2726770; //WxAM img decoder

			if (fileType == "video") {
				*(int32_t*)(a2 + 0xD8) = 4;
				*(int32_t*)(a2 + 0x1A8) = 0;
				*(int32_t*)(a2 + 0x1E0) = 2;
				*(int32_t*)(a2 + 0x334) = 1;
				*(uint64_t*)(a2 + 0x520) = 0;
			}
			//NetSceneDownloadAppAttach (请求不一样)
			if (fileType == "file") {
				return -1;
			}
			
			struct Fake {
				virtual ~Fake() {}
				virtual uint64_t _1() { return 0; }
				virtual uint64_t _2() { return 0; }
				virtual uint64_t _3() { return 0; }
				virtual uint64_t _4() { return 0; }
				virtual uint64_t _5() { return 0; }
			};

			Fake fake;

			function::__Instance instance = (function::__Instance)(base_+ offset::kCDNServicecs);
			function::__StartupDownloadMedia StartupDownloadMedia = (function::__StartupDownloadMedia)(base_ + offset::kStartupDownloadMedia);

			return StartupDownloadMedia(instance(), reinterpret_cast<UINT64>(&cdnDownload), reinterpret_cast<UINT64>(&fake),0);
		}



		int64_t WeChat::GetSelfInfo(common::SelfInfo& out) {
			int64_t success = -1;
			function::__Instance  instance = (function::__Instance)(base_ + offset::kAccountServiceMgr);
			function::__GetDataSavePath GetDataSavePath = (function::__GetDataSavePath)(base_ + offset::kGetAppDataSavePath);
			function::__GetCurrentDataPath GetCurrentDataPath = (function::__GetCurrentDataPath)(base_ + offset::kGetCurrentDataPath);
			uint64_t service_addr = instance();
			if (service_addr) {
				if (*(int64_t*)(service_addr + 0x80) == 0 ||
					*(int64_t*)(service_addr + 0x80 + 0x10) == 0) {
					out.Wxid = std::string();
				}
				else {
					if (*(int64_t*)(service_addr + 0x80 + 0x18) == 0xF) {
						out.Wxid = std::string((char*)(service_addr + 0x80),
							*(int64_t*)(service_addr + 0x80 + 0x10));
					}
					else {
						out.Wxid = std::string(*(char**)(service_addr + 0x80),
							*(int64_t*)(service_addr + 0x80 + 0x10));
					}
				}

				if (*(int64_t*)(service_addr + 0x108) == 0 ||
					*(int64_t*)(service_addr + 0x108 + 0x10) == 0) {
					out.Account = std::string();
				}
				else {
					if (*(int64_t*)(service_addr + 0x108 + 0x18) == 0xF) {
						out.Account = std::string((char*)(service_addr + 0x108),
							*(int64_t*)(service_addr + 0x108 + 0x10));
					}
					else {
						out.Account = std::string(*(char**)(service_addr + 0x108),
							*(int64_t*)(service_addr + 0x108 + 0x10));
					}
				}

				if (*(int64_t*)(service_addr + 0x128) == 0 ||
					*(int64_t*)(service_addr + 0x128 + 0x10) == 0) {
					out.Mobile = std::string();
				}
				else {
					if (*(int64_t*)(service_addr + 0x128 + 0x18) == 0xF) {
						out.Mobile = std::string((char*)(service_addr + 0x128),
							*(int64_t*)(service_addr + 0x128 + 0x10));
					}
					else {
						out.Mobile = std::string(*(char**)(service_addr + 0x128),
							*(int64_t*)(service_addr + 0x128 + 0x10));
					}
				}

				if (*(int64_t*)(service_addr + 0x148) == 0 ||
					*(int64_t*)(service_addr + 0x148 + 0x10) == 0) {
					out.Signature = std::string();
				}
				else {
					if (*(int64_t*)(service_addr + 0x148 + 0x18) == 0xF) {
						out.Signature = std::string((char*)(service_addr + 0x148),
							*(int64_t*)(service_addr + 0x148 + 0x10));
					}
					else {
						out.Signature = std::string(*(char**)(service_addr + 0x148),
							*(int64_t*)(service_addr + 0x148 + 0x10));
					}
				}

				if (*(int64_t*)(service_addr + 0x168) == 0 ||
					*(int64_t*)(service_addr + 0x168 + 0x10) == 0) {
					out.Country = std::string();
				}
				else {
					if (*(int64_t*)(service_addr + 0x168 + 0x18) == 0xF) {
						out.Country = std::string((char*)(service_addr + 0x168),
							*(int64_t*)(service_addr + 0x168 + 0x10));
					}
					else {
						out.Country = std::string(*(char**)(service_addr + 0x168),
							*(int64_t*)(service_addr + 0x168 + 0x10));
					}
				}

				if (*(int64_t*)(service_addr + 0x188) == 0 ||
					*(int64_t*)(service_addr + 0x188 + 0x10) == 0) {
					out.Province = std::string();
				}
				else {
					if (*(int64_t*)(service_addr + 0x188 + 0x18) == 0xF) {
						out.Province = std::string((char*)(service_addr + 0x188),
							*(int64_t*)(service_addr + 0x188 + 0x10));
					}
					else {
						out.Province = std::string(*(char**)(service_addr + 0x188),
							*(int64_t*)(service_addr + 0x188 + 0x10));
					}
				}

				if (*(int64_t*)(service_addr + 0x1A8) == 0 ||
					*(int64_t*)(service_addr + 0x1A8 + 0x10) == 0) {
					out.City = std::string();
				}
				else {
					if (*(int64_t*)(service_addr + 0x1A8 + 0x18) == 0xF) {
						out.City = std::string((char*)(service_addr + 0x1A8),
							*(int64_t*)(service_addr + 0x1A8 + 0x10));
					}
					else {
						out.City = std::string(*(char**)(service_addr + 0x1A8),
							*(int64_t*)(service_addr + 0x1A8 + 0x10));
					}
				}

				if (*(int64_t*)(service_addr + 0x1E8) == 0 ||
					*(int64_t*)(service_addr + 0x1E8 + 0x10) == 0) {
					out.Name = std::string();
				}
				else {
					if (*(int64_t*)(service_addr + 0x1E8 + 0x18) == 0xF) {
						out.Name = std::string((char*)(service_addr + 0x1E8),
							*(int64_t*)(service_addr + 0x1E8 + 0x10));
					}
					else {
						out.Name = std::string(*(char**)(service_addr + 0x1E8),
							*(int64_t*)(service_addr + 0x1E8 + 0x10));
					}
				}

				if (*(int64_t*)(service_addr + 0x450) == 0 ||
					*(int64_t*)(service_addr + 0x450 + 0x10) == 0) {
					out.HeadImg = std::string();
				}
				else {
					out.HeadImg = std::string(*(char**)(service_addr + 0x450),
						*(int64_t*)(service_addr + 0x450 + 0x10));
				}

				if (*(int64_t*)(service_addr + 0x7B8) == 0 ||
					*(int64_t*)(service_addr + 0x7B8 + 0x10) == 0) {
					out.PublicKey = std::string();
				}
				else {
					out.PublicKey = std::string(*(char**)(service_addr + 0x7B8),
						*(int64_t*)(service_addr + 0x7B8 + 0x10));
				}

				if (*(int64_t*)(service_addr + 0x7D8) == 0 ||
					*(int64_t*)(service_addr + 0x7D8 + 0x10) == 0) {
					out.PrivateKey = std::string();
				}
				else {
					out.PrivateKey = std::string(*(char**)(service_addr + 0x7D8),
						*(int64_t*)(service_addr + 0x7D8 + 0x10));
				}

				if (*(int64_t*)(service_addr + 0x6E0) == 0 ||
					*(int64_t*)(service_addr + 0x6E8) == 0) {
					out.Dbkey = std::string();
				}
				else {
					int64_t byte_addr = *(int64_t*)(service_addr + 0x6E0);
					int64_t len = *(int64_t*)(service_addr + 0x6E8);
					out.Dbkey = utils::Bytes2Hex((BYTE*)byte_addr, static_cast<int>(len));
				}

				uint64_t flag = *(uint64_t*)(service_addr + 0x7F8);
				if (flag == 1) {
					common::WeChatWString currentDataPath;
					GetCurrentDataPath(reinterpret_cast<ULONG_PTR>(&currentDataPath));
					if (currentDataPath.buf) {
						out.CurrentDataPath = utils::WstringToUtf8(
							std::wstring(currentDataPath.buf, currentDataPath.len));
					}
					else {
						out.CurrentDataPath = std::string();
					}
				}
				common::WeChatWString  dataSavePath;
				GetCurrentDataPath(reinterpret_cast<ULONG_PTR>(&dataSavePath));
				if (dataSavePath.buf) {
					out.DataSavePath = utils::WstringToUtf8(
						std::wstring(dataSavePath.buf, dataSavePath.len));
				}
				else {
					out.DataSavePath = std::string();
				}
				success = 1;
				return success;
			}
		}
	}
}