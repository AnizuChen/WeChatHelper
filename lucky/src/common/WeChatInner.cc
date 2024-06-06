#include "WeChatInner.h"
#include "utils/Utils.h"
#include <sstream>
#include <regex>

namespace lucky {
	namespace common {

		std::string mmString::toString() {
			if (len > 0) {
				return utils::WstringToUtf8(std::wstring(buf, len));
			}
			return "";
		}

		std::string ChatRoomInfo::ToJson() {
			std::stringstream ss;
			ss << "{";
			ss << "\"ChatRoomName\":" << "\"" << ChatRoomName << "\"" << ",";
			ss << "\"Announcement\":" << "\"" << Announcement << "\"" << ",";
			ss << "\"AnnouncementEditor\":" << "\"" << AnnouncementEditor << "\"" << ",";
		

			ss << "\"InfoVersion\":" << InfoVersion << ",";
			ss << "\"AnnouncementPublishTime\":" << AnnouncementPublishTime << ",";
			ss << "\"ChatRoomStatus\":" << ChatRoomStatus << ",";
			ss << "\"Reserved1\":" << Reserved1 << ",";


			ss << "\"Reserved2\":" << "\"" << Reserved2 << "\"" << ",";
			ss << "\"Reserved4\":" << "\"" << Reserved4 << "\"" << ",";
			ss << "\"Reserved6\":" << "\"" << Reserved6 << "\"" << ",";
			ss << "\"Reserved8\":" << "\"" << Reserved8 << "\"" << ",";

			ss << "\"Reserved3\":" << Reserved3 << ",";
			ss << "\"Reserved5\":" << Reserved5 << ",";
			ss << "\"Reserved7\":" << Reserved7 << ",";
			

			ss << "}";
			return ss.str();
		}


		std::string escapeBackslashes(const std::string& path) {
			std::regex backslash_regex(R"(\\)");
			return std::regex_replace(path, backslash_regex, "\\\\");
		}

		std::string SelfInfo::ToJson() {
			std::stringstream ss;
			ss << "{";
			ss << "\"Name\":" << "\"" << Name << "\"" << ",";
			ss << "\"City\":" << "\"" << City << "\"" << ",";
			ss << "\"Province\":" << "\"" << Province << "\"" << ",";
			ss << "\"Country\":" << "\"" << Country << "\"" << ",";
			ss << "\"Account\":" << "\"" << Account << "\"" << ",";
			ss << "\"Wxid\":" << "\"" << Wxid << "\"" << ",";

			ss << "\"Mobile\":" << "\"" << Mobile << "\"" << ",";
			ss << "\"HeadImg\":" << "\"" << HeadImg << "\"" << ",";

			ss << "\"Signature\":" << "\"" << Signature << "\"" << ",";

			ss << "\"DataSavePath\":" << "\"" << escapeBackslashes(DataSavePath) << "\"" << ",";
			ss << "\"CurrentDataPath\":" << "\"" << escapeBackslashes(CurrentDataPath) << "\"" << ",";

			ss << "\"Dbkey\":" << "\"" << Dbkey << "\"" << ",";
			ss << "\"PublicKey\":" << "\"" << PublicKey << "\"" << ",";
			ss << "\"PrivateKey\":" << "\"" << PrivateKey << "\"" ;


			ss << "}";
			return ss.str();


		}

		void ChatRoomInfoCast::Cast(ChatRoomInfo& info){
			info.ChatRoomName = ChatRoomName.toString();
			info.Announcement = Announcement.toString();
			info.AnnouncementEditor = AnnouncementEditor.toString();
			
			info.InfoVersion = InfoVersion;
			info.AnnouncementPublishTime = AnnouncementPublishTime;
			info.ChatRoomStatus = ChatRoomStatus;
			info.Reserved1 = Reserved1;

			info.Reserved2 = Reserved2.toString();
			info.Reserved4 = Reserved4.toString();
			info.Reserved6  = Reserved6.toString();
			info.Reserved8 = Reserved8.toString();

			info.Reserved3 = Reserved3;
			info.Reserved5 = Reserved5;
			info.Reserved7 = Reserved7;

		}

		ChatRoomInfoCast::~ChatRoomInfoCast() {

		}

		ContactCast::~ContactCast() {

		}

		void ContactCast::Cast(Contact& contact) {
			contact.UserName = UserName.toString();
			contact.Alias = Alias.toString();
			contact.EncryptUserName = EncryptUserName.toString();
			contact.DelFlag = DelFlag;
			contact.Type = Type;
			contact.VerifyFlag = VerifyFlag;
			contact.Remark = Remark.toString();
			contact.NickName = NickName.toString();
			contact.LabelIDList = LabelIDList.toString();
			contact.DomainList = DomainList.toString();
			contact.ChatRoomType = ChatRoomType;
			contact.PYInitial = PYInitial.toString();
			contact.QuanPin = QuanPin.toString();
			contact.RemarkPYInitial = RemarkPYInitial.toString();
			contact.RemarkQuanPin = RemarkQuanPin.toString();
			contact.BigHeadImgUrl = BigHeadImgUrl.toString();
			contact.SmallHeadImgUrl = SmallHeadImgUrl.toString();


			contact.ImgFlag = ImgFlag;
			contact.Sex =		 Sex;
			contact.ContactType =   ContactType;

			contact.Weibo   = Weibo.toString();
			contact.WeiboFlag	 = 	  WeiboFlag;
			contact.WeiboNickname =   WeiboNickname.toString();

			contact.PersonalCard =	   PersonalCard;

			contact.Signature =  Signature.toString();
			contact.Country =  Country.toString();

			
			for (auto it : PhoneNumberList) {
				contact.PhoneNumberList.emplace_back(it.toString());
			}

			contact.Province =   Province.toString();
			contact.City =   City.toString();

			contact.Source =    Source;

			contact.VerifyInfo =  VerifyInfo.toString();
			contact.RemarkDesc = RemarkDesc.toString();
			contact.RemarkImgUrl =  RemarkImgUrl.toString();

			contact.BitMask =    BitMask;
			contact.BitVal =    BitVal;
			contact.AddContactScene =     AddContactScene;
			contact.HasWeiXinHdHeadImg =   HasWeiXinHdHeadImg;
			contact.Level =   Level;

			contact.VerifyContent =   VerifyContent.toString();

			contact.AlbumStyle = 		AlbumStyle;
			contact.AlbumFlag = 		AlbumFlag;
			contact.AlbumBGImgID = AlbumBGImgID.toString();

			contact.SnsFlag =		SnsFlag;
			contact.SnsBGImgID =	SnsBGImgID.toString();
			contact.SnsBGObjectID =   SnsBGObjectID;
			contact.SnsFlagEx =		 SnsFlagEx;

			contact.IDCardNum =  IDCardNum.toString();
			contact.RealName =  RealName.toString();
			contact.MobileHash =  MobileHash.toString();
			contact.MobileFullHash =  MobileFullHash.toString();
			contact.ExtInfo =  ExtInfo.toString();
			contact.CardImgUrl =  CardImgUrl.toString();
			
		}

		std::string Contact::ToJson() {
			std::stringstream ss;
			ss << "{";
			ss << "\"UserName\":" << "\"" << UserName << "\"" << ",";
			ss << "\"Alias\":" << "\"" << Alias << "\"" << ",";
			ss << "\"EncryptUserName\":" << "\"" << EncryptUserName << "\"" << ",";
			ss << "\"DelFlag\":"  << DelFlag  << ",";
			ss << "\"Type\":" << Type << ",";
			ss << "\"VerifyFlag\":" << VerifyFlag << ",";
			ss << "\"Remark\":" << "\"" << Remark << "\"" << ",";
			ss << "\"NickName\":" << "\"" << NickName << "\"" << ",";
			ss << "\"LabelIDList\":" << "\"" << LabelIDList << "\"" << ",";
			ss << "\"DomainList\":" << "\"" << DomainList << "\"" << ",";
			ss << "\"ChatRoomType\":" << ChatRoomType << ",";
			ss << "\"PYInitial\":" << "\"" << PYInitial << "\"" << ",";
			ss << "\"QuanPin\":" << "\"" << QuanPin << "\"" << ",";
			ss << "\"RemarkPYInitial\":" << "\"" << RemarkPYInitial << "\"" << ",";
			ss << "\"RemarkQuanPin\":" << "\"" << RemarkQuanPin << "\"" << ",";
			ss << "\"BigHeadImgUrl\":" << "\"" << BigHeadImgUrl << "\"" << ",";
			ss << "\"SmallHeadImgUrl\":" << "\"" << SmallHeadImgUrl << "\"" << ",";
			ss << "\"ImgFlag\":" << ImgFlag << ",";
			ss << "\"Sex\":" << Sex << ",";
			ss << "\"ContactType\":" << ContactType << ",";
			ss << "\"Weibo\":" << "\"" << Weibo << "\"" << ",";
			ss << "\"WeiboFlag\":" << WeiboFlag << ",";
			ss << "\"WeiboNickname\":" << "\"" << WeiboNickname << "\"" << ",";
			ss << "\"PersonalCard\":" << PersonalCard << ",";
			ss << "\"Signature\":" << "\"" << Signature << "\"" << ",";
			ss << "\"Country\":" << "\"" << Country << "\"" << ",";

		
			if (!PhoneNumberList.empty()) {
				ss << "\"PhoneNumberList\":[\"0\",";
				for (auto it : PhoneNumberList) {
					ss << "\"" << it << "\"" ;
				}
				ss << "],";
			} 

			ss << "\"Province\":" << "\"" << Province << "\"" << ",";
			ss << "\"City\":" << "\"" << City << "\"" << ",";
			ss << "\"Source\":" << Source << ",";
			ss << "\"VerifyInfo\":" << "\"" << VerifyInfo << "\"" << ",";
			ss << "\"RemarkDesc\":" << "\"" << RemarkDesc << "\"" << ",";
			ss << "\"RemarkImgUrl\":" << "\"" << RemarkImgUrl << "\"" << ",";
			ss << "\"BitMask\":" << BitMask << ",";
			ss << "\"BitVal\":" << BitVal << ",";
			ss << "\"AddContactScene\":" << AddContactScene << ",";
			ss << "\"HasWeiXinHdHeadImg\":" << HasWeiXinHdHeadImg << ",";
			ss << "\"Level\":" << Level << ",";
			ss << "\"VerifyContent\":" << "\"" << VerifyContent << "\"" << ",";
			ss << "\"AlbumStyle\":" << AlbumStyle << ",";
			ss << "\"AlbumFlag\":" << AlbumFlag << ",";
			ss << "\"AlbumBGImgID\":" << "\"" << AlbumBGImgID << "\"" << ",";
			ss << "\"SnsFlag\":" << SnsFlag << ",";
			ss << "\"SnsBGImgID\":" << "\"" << SnsBGImgID << "\"" << ",";
			ss << "\"SnsBGObjectID\":" << "\"" << SnsBGObjectID << "\"" << ",";
			ss << "\"SnsFlagEx\":" << SnsFlagEx << ",";
			ss << "\"IDCardNum\":" << "\"" << IDCardNum << "\"" << ",";
			ss << "\"RealName\":" << "\"" << RealName << "\"" << ",";
			ss << "\"MobileHash\":" << "\"" << MobileHash << "\"" << ",";
			ss << "\"MobileFullHash\":" << "\"" << MobileFullHash << "\"" << ",";
			ss << "\"ExtInfo\":" << "\"" << ExtInfo << "\"" << ",";
			ss << "\"CardImgUrl\":" << "\"" << CardImgUrl << "\"" ;
			ss << "}";
			return ss.str();
		}
		
	}
}