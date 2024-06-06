#ifndef _WECHAT_FUNCTION_H_
#define _WECHAT_FUNCTION_H_

namespace lucky {
namespace wechat {
namespace function {

typedef uint64_t (*__GetDataSavePath)(uint64_t);
typedef uint64_t (*__GetCurrentDataPath)(uint64_t);

typedef uint64_t (*__SendFile)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t,
                             uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

typedef uint64_t (*__GetContactList)(uint64_t, uint64_t);
typedef uint64_t(*__GetContact)(uint64_t, uint64_t, uint64_t);

typedef char(*__DelContact)(uint64_t, uint64_t);
typedef char(*__VerifyUser)(uint64_t, uint64_t, int, uint64_t, int, uint64_t, uint64_t, int);

typedef uint64_t(*__RemarkContact)(uint64_t, uint64_t, uint64_t);
typedef uint64_t(*__BlackContact)(uint64_t, uint64_t, uint32_t);
typedef uint64_t (*__DoModChatRoomMemberNickName)(uint64_t, uint64_t, uint64_t, uint64_t);
typedef uint64_t (*__GetMemberFromChatRoom)(uint64_t, uint64_t, uint64_t);
typedef uint64_t (*__NewChatRoom)(uint64_t);
typedef uint64_t (*__FreeChatRoom)(uint64_t);

typedef uint64_t (*__DoTopMsg)(uint64_t, uint64_t);
typedef uint64_t (*__RemoveTopMsg)(uint64_t, uint64_t, uint64_t);

typedef uint64_t (*__QuitChatRoom)(uint64_t, uint64_t, uint64_t);
typedef uint64_t (*__ForwardMsg)(uint64_t, uint64_t, uint64_t, uint64_t);

//构造函数&析构函数
typedef uint64_t(*__Constructor)(uint64_t);
typedef uint64_t(*__Destructor)(uint64_t);

//单例实例函数
typedef uint64_t(*__Instance)();

//SearchContact
typedef uint64_t(*__SearchContactCallBack)(uint64_t, uint64_t,char);
typedef uint64_t(*__StartSearchFromScene)(uint64_t, uint64_t);

//NetScene 
typedef char(*__NetSceneGetContact)(uint64_t, uint64_t, uint64_t);
typedef uint64_t(*__NetSceneGetContactLabelList)();
typedef uint64_t(*__NetSceneAddContactLabel)(uint64_t, uint32_t , uint64_t, uint32_t );
typedef uint64_t(*__NewContactLabelIdStruct)(uint64_t);
typedef uint64_t(*__DelContactLabel)(uint64_t, uint64_t);
typedef uint64_t(*__ModifyContactLabel)(uint64_t, uint64_t);
typedef  uint8_t(*__SceneNetSceneBase)(uint64_t, uint64_t);

typedef uint64_t(*__SendTextMsg)(uint64_t, uint64_t, uint64_t, uint64_t, uint32_t, uint32_t,
    uint32_t, uint64_t);
typedef uint64_t(*__SendImageMsg)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);


typedef  uint8_t(*__SendPatMsg)(uint64_t, uint64_t, uint64_t);

typedef  uint64_t(*__GetContactCardContent)(uint64_t, uint64_t);

typedef void(*__DoAddMsg)(uint64_t, uint64_t, uint64_t);

typedef void(*__CreateChatRoom)(uint64_t, uint64_t);

typedef uint8_t(*__GetChatRoomDetailInfo)(uint64_t, uint64_t, uint64_t, uint8_t);

typedef uint64_t(*__GetChatroomMemberDetail)(uint64_t, uint64_t, uint32_t);
typedef uint8_t(*__DoAddMemberToChatRoom)(uint64_t, uint64_t, uint64_t, uint64_t);
typedef uint8_t(*__InviteMemberToChatRoom)(uint64_t, uint64_t, uint64_t, uint64_t);
typedef uint8_t(*__DoDelMemberFromChatRoom)(uint64_t, uint64_t, uint64_t);
typedef uint8_t(*__QuitAndDelChatRoom)(uint64_t, uint64_t, int8_t);
typedef uint8_t(*__ModChatRoomTopic)(uint64_t, uint64_t, uint64_t);

typedef uint64_t(*__GetA8Key)(uint64_t, uint64_t, int32_t, uint32_t, int32_t, uint64_t, uint64_t, int32_t, int32_t);


typedef uint64_t(*__TimelineGetFirstPage)(uint64_t, int8_t);
typedef uint64_t(*__TimelineGetNextPage)(uint64_t, uint64_t);
typedef uint64_t(*__SnsObjectDetail)(uint64_t, uint64_t);
typedef uint64_t(*__SnsObjectLike)(uint64_t, uint64_t, uint64_t ,uint64_t);
typedef uint64_t(*__SnsObjectOp)(uint64_t, uint64_t, int , int , uint64_t);
typedef void(*__SnsObjectDoComment)(uint64_t, uint64_t, int, int, uint64_t);

typedef uint64_t(*__StartupDownloadMedia)(uint64_t , uint64_t , uint64_t , unsigned int );



} // namespace function
}  // namespace wechat
}  // namespace lucky
#endif