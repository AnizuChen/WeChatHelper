#ifndef _WECHAT_OFFSET_H_
#define _WECHAT_OFFSET_H_
#include <cstdint>

namespace  lucky{

namespace wechat {

namespace offset {


//3.9.10.27
const uint64_t kGetContactMgr = 0x1C0BDE0;
const uint64_t kSearchContactMgr = 0x2065F80;
const uint64_t kChatRoomMgr = 0x1C4E200;
const uint64_t kOpLogMgr = 0x1C193C0;
const uint64_t kSnsTimeLineMgr = 0x2E6B110;
const uint64_t kCDNServicecs = 0x1CAE4E0;
const uint64_t kAccountServiceMgr = 0x1C1FE90;

const uint64_t kGetAppDataSavePath = 0x26A7780;
const uint64_t kGetCurrentDataPath = 0x2314E40;

const uint64_t kNewContact = 0x25E3650;
const uint64_t kFreeContact = 0x25E3D00;
const uint64_t kGetContact = 0x225F950;
const uint64_t kDelContact = 0x2263490;
const uint64_t kGetContactList = 0x2265540;
const uint64_t kRemarkContact = 0x22550D0;
const uint64_t kBlackContact = 0x2255310;
const uint64_t kGetContactCardContent = 0x2200BB0;

const uint64_t kVerifyUser = 0x225C340;								// ContactMgr::doVerifyUser 
const uint64_t kStartSearchFromScene = 0x2370010;					//SearchContactMgr::StartSearchFromScene
const uint64_t kNetSceneGetContact = 0x225D060;						//new NetSceneBatchGetContact (id:%d)
const uint64_t kNetSceneGetContactLabelList = 0x2245F00;            //NetSceneGetContactLabelList::NetSceneGetContactLabelList

const uint64_t kSceneCenter = 0x1CDD710;
const uint64_t kSceneNetSceneBase = 0x2454EB0;

const uint64_t kNewContactLabelIdStruct = 0x2189150;
const uint64_t kNetSceneAddContactLabel = 0x245BE40;                //NetSceneAddContactLabel::NetSceneAddContactLabel
const uint64_t kNetSceneDelContactLabel = 0x248F410;      

const uint64_t kNetSceneModifyContactLabel = 0x250C480;

const uint64_t kSendMessageMgr = 0x1C1E690;
const uint64_t kAppMsgMgr = 0x1C23630;

const uint64_t kSendTextMsg = 0x238DDD0;
const uint64_t kSendImageMsg = 0x2383560;
const uint64_t kSendFileMsg = 0x21969E0;
const uint64_t kSendPatMsg = 0x2D669B0;

const uint64_t kFreeChatMsg = 0x1C1FF10;
const uint64_t kNewChatMsg = 0x1C28800;

const uint64_t kCreateChatRoom = 0x221AF50;
const uint64_t kChatRoomInfoConstructor = 0x25CF470;
const uint64_t kGetChatRoomDetailInfo = 0x222BEA0;
const uint64_t kGetChatroomMemberDetail = 0x2226C80;
const uint64_t kDoAddMemberToChatRoom = 0x221B8A0;
const uint64_t kDoDelMemberFromChatRoom = 0x221BEE0;
const uint64_t kInviteMemberToChatRoom = 0x221B280;
const uint64_t kQuitAndDelChatRoom = 0x2225EF0;
const uint64_t kModChatRoomTopic = 0x2364610;
const uint64_t kGetA8Key = 0x24ABD40;

const uint64_t kTimelineGetFirstPage = 0x2EFE660;
const uint64_t kTimelineGetNextPage = 0x2EFEC00;
const uint64_t kSnsObjectDetail = 0x2EFDEC0;
const uint64_t kSnsObjectLike = 0x2F113D0;
const uint64_t kSnsObjectOp = 0x2F13670;
const uint64_t kSnsObjectDoComment = 0x2EFD0F0;

const uint64_t kStartupDownloadMedia = 0x2596780;

const uint64_t kDoAddMsg = 0x23D2B10;

const uint64_t kSceneCenterStartTask = 0x2454F70;					//must do scene after auth
const uint64_t kMessageLoop = 0x397B400;							//Chrome.MessageLoopProblem (__int64 a1, __int64 a2)
const uint64_t kWMDestroy = 0x2119240;								//Message WM_DESTROY



}  // namespace offset
}  // namespace wechat
}  // namespace lucky

#endif