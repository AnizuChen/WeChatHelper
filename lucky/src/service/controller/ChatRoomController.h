#ifndef _CHATROOMCONTROLLER_H
#define _CHATROOMCONTROLLER_H

#include "HttpController.h"

namespace lucky {

	namespace service {

		namespace controller {

			class ChatRoomController : public HttpController<ChatRoomController> {

			public:
				PATHS_BEGIN

				ADD_PATH("/api/netscene/createchatroom", NetSceneCreateChatRoom);
				ADD_PATH("/api/netscene/getmemberfromchatroom", NetSceneGetMemberFromChatRoom);

				ADD_PATH("/api/wechat/getchatroomdetailinfo", GetChatRoomDetailInfo);
				ADD_PATH("/api/wechat/addmembertchatroom", AddMemberToChatRoom);
				ADD_PATH("/api/wechat/invitemembertochatroom", InviteMemberToChatRoom);
				ADD_PATH("/api/wechat/delmemberfromchatroom", DelMemberFromChatRoom);

				ADD_PATH("/api/wechat/quitanddelchatroom", QuitAndDelChatRoom);
				
				ADD_PATH("/api/wechat/topmsg", TopMsg);
				ADD_PATH("/api/wechat/closetopmsg", CloseTopMsg);

				ADD_PATH("/api/wechat/modchatroomtopic", ModChatRoomTopic);
				ADD_PATH("/api/wechat/modchatroommembernickname", ModChatRoomMemberNickName);
				ADD_PATH("/api/wechat/setchatroomannouncement", SetChatRoomAnnouncement);

				//扫码进群以及群邀请进群 先拿到群邀请或者群二维码里面的链接通过A8KEY拿到FullURL访问这个即可
				


				PATHS_END

				static std::string NetSceneCreateChatRoom(std::string params);
				static std::string NetSceneGetMemberFromChatRoom(std::string params);
				static std::string GetChatRoomDetailInfo(std::string params);
				static std::string AddMemberToChatRoom(std::string params);
				static std::string InviteMemberToChatRoom(std::string params);
				static std::string DelMemberFromChatRoom(std::string params);
				static std::string QuitAndDelChatRoom(std::string params);
				static std::string TopMsg(std::string params);
				static std::string CloseTopMsg(std::string params);
				static std::string ModChatRoomTopic(std::string params);
				static std::string ModChatRoomMemberNickName(std::string params);
				static std::string SetChatRoomAnnouncement(std::string params);
			};
		}
	}

}

#endif // !_CHATROOMCONTROLLER_H
