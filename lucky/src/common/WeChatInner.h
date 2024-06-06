#ifndef _WECHAT_INNER_H
#define _WECHAT_INNER_H


#include <cstdint>
#include <string>
#include <vector>

namespace lucky {
	namespace common {

		struct mmString {
			wchar_t* buf = nullptr;
			int32_t		len = 0;
			int32_t     cap = 0;
			int64_t		c_ptr = 0;
			int32_t		c_len = 0;
			int32_t		c_cap = 0;
			std::string toString();
		};

		struct Contact {
			std::string   ToJson();
			std::string   UserName;
			std::string   Alias;
			std::string   EncryptUserName;
			int32_t		  DelFlag;
			int32_t       Type;
			int32_t       VerifyFlag;
			std::string   Remark;
			std::string   NickName;
			std::string   LabelIDList;
			std::string   DomainList;
			int64_t       ChatRoomType;
			std::string   PYInitial;
			std::string   QuanPin;
			std::string   RemarkPYInitial;
			std::string   RemarkQuanPin;
			std::string   BigHeadImgUrl;
			std::string   SmallHeadImgUrl;

			int32_t	      ImgFlag;			  
			int32_t       Sex;				  
			int32_t       ContactType;	

			std::string   Weibo;				
			int32_t		  WeiboFlag;
			std::string   WeiboNickname;	

			int32_t	      PersonalCard;		 

			std::string   Signature;		  
			std::string   Country;			

			std::vector<std::string>  PhoneNumberList; 

			std::string  Province;			
			std::string  City;			

			int32_t   Source;			
	
			std::string  VerifyInfo;			
			std::string  RemarkDesc;		   
			std::string  RemarkImgUrl;		 

			int32_t   BitMask;			  
			int32_t   BitVal;			 
			int32_t   AddContactScene;	  
			int32_t   HasWeiXinHdHeadImg; 
			int32_t   Level;			
		
			std::string  VerifyContent;     

			int32_t		AlbumStyle;	      
			int32_t		AlbumFlag;			  
			std::string AlbumBGImgID;		  

			int32_t  SnsFlag;			
			std::string  SnsBGImgID;		
			int64_t  SnsBGObjectID;		
			int32_t  SnsFlagEx;			

			std::string IDCardNum;			
			std::string RealName;			
			std::string MobileHash;		
			std::string MobileFullHash;    
			std::string ExtInfo;		
			std::string CardImgUrl;	  
		};


		struct ChatRoomInfo {
			std::string   ToJson();
			std::string ChatRoomName;
			std::string Announcement;
			std::string AnnouncementEditor;

			uint32_t InfoVersion = 0;
			uint32_t AnnouncementPublishTime = 0;
			uint32_t ChatRoomStatus = 0;
			uint32_t Reserved1 = 0;

			std::string Reserved2;
			std::string Reserved4;
			std::string Reserved6;
			std::string Reserved8;

			uint32_t Reserved3 = 0;
			uint32_t Reserved5 = 0;
			uint64_t Reserved7 = 0;

			std::string m8;
			std::string m9;
		};

		struct ChatMsg {
			
		};

		struct SelfInfo {
			std::string   ToJson();
			std::string Name;
			std::string City;
			std::string Province;
			std::string Country;
			std::string Account;
			std::string Wxid;
			std::string Mobile;
			std::string HeadImg;
			std::string DataSavePath;
			std::string Signature;
			std::string CurrentDataPath;
			std::string Dbkey;
			std::string PublicKey;
			std::string PrivateKey;
		};
		

		struct ChatRoomInfoCast {
			void Cast(ChatRoomInfo&);
			virtual ~ChatRoomInfoCast();

			mmString ChatRoomName;
			mmString Announcement;
			mmString AnnouncementEditor;
			
			uint32_t InfoVersion;
			uint32_t AnnouncementPublishTime;
			uint32_t ChatRoomStatus;
			uint32_t Reserved1;

			mmString Reserved2;
			mmString Reserved4;
			mmString Reserved6;
			mmString Reserved8;

			uint32_t Reserved3;
			uint32_t Reserved5;
			uint64_t Reserved7;

			mmString m8;
			mmString m9;
		};


		struct ContactCast {
			void       Cast(Contact&);
			virtual	  ~ContactCast();		//vptr; 0x00 
			int64_t	   _BitMask = 0;	    //0x8;  + 0x8
			mmString   UserName;			//0x10  + 0x20
			mmString   Alias;				//0x30  + 0x20
			mmString   EncryptUserName;		//0x50  + 0x20
			int32_t	   DelFlag;				//0x70  + 0x4
			int32_t    Type;				//0x74  + 0x4
			int32_t    VerifyFlag;			//0x78  + 0x4
			int32_t	   _0x7C;				//0x7C  + 0x4
			mmString   Remark;				//0x80  + 0x20
			mmString   NickName;			//0xA0  + 0x20
			mmString   LabelIDList;			//0xC0  + 0x20
			mmString   DomainList;			//0xE0  + 0x20
			int64_t    ChatRoomType;		//0x100 + 0x8
			mmString   PYInitial;			//0x108 + 0x20
			mmString   QuanPin;				//0x128 + 0x20
			mmString   RemarkPYInitial;		//0x148 + 0x20
			mmString   RemarkQuanPin;		//0x168 + 0x20
			mmString   BigHeadImgUrl;		//0x188 + 0x20
			mmString   SmallHeadImgUrl;		//0x1A8 + 0x20

			mmString   _HeadImgMd5;			//0x1C8 + 0x20 //这里格式不一样不要解析 只占位

			//int64_t  ChatRoomNotify;      //0x1E8
	
			char       _0x1E8[24];			//0x1E8 + 0x18
			mmString   ExtraBuf;			//0x200 + 0x20

			int32_t    ImgFlag;			   //0x220 + 0x4
			int32_t    Sex;				   //0x224 + 0x4
			int32_t    ContactType;		   //0x228 + 0x4
			int32_t   _0x22C;			   //0x22c + 0x4

			mmString  Weibo;				//0x230 + 0x20
			int32_t   WeiboFlag;			//0x250 + 0x4
			int32_t   _0x254;				//0x254 + 0x4

			mmString  WeiboNickname;		//0x258 + 0x20

			int32_t  PersonalCard;		   //0x278 + 0x4
			int32_t  _0x27C;			   //0x27c + 0x4
			
			mmString  Signature;		  //0x280 + 0x20
			mmString  Country;			  //0x2A0 + 0x20

			std::vector<mmString>  PhoneNumberList; //0x2C0 + 0x18

			mmString  Province;				//0x2D8 + 0x20
			mmString  City;					//0x2F8 + 0x20

			int32_t   Source;				//0x318 + 0x4
			int32_t   _0x31C;				//0x31C + 0x4

			mmString  VerifyInfo;			//0x320 + 0x20
			mmString  RemarkDesc;		   //0x340 + 0x20
			mmString  RemarkImgUrl;		   //0x360 + 0x20

			int32_t   BitMask;			  //0x380 + 0x4
			int32_t   BitVal;			  //0x384 + 0x4
			int32_t   AddContactScene;	  //0x388 + 0x4
			int32_t   HasWeiXinHdHeadImg; //0x38c + 0x4
			int32_t   Level;			  //0x390 + 0x4
			int32_t   _0x394;			  //0x394 + 0x4

			mmString  VerifyContent;      //0x398 + 0x20

			int32_t  AlbumStyle;	      //0x3B8 + 0x4
			int32_t  AlbumFlag;			  //0x3BC + 0x4
			mmString AlbumBGImgID;		  //0x3C0 + 0x20

			int64_t  _0x3E0;			 //0x3E0 + 0x8

			int32_t  SnsFlag;			//0x3E8	+ 0x4
			int32_t  _0x3EC;			//0x3EC + 0x4

			mmString  SnsBGImgID;		//0x3F0 + 0x20

			int64_t  SnsBGObjectID;		//0x410 + 0x8

			int32_t  SnsFlagEx;			//0x418 + 0x4
			int32_t  _0x41C;			//0x41C + 0x4

			mmString IDCardNum;			//0x420 + 0x20
			mmString RealName;			//0x440 + 0x20

			mmString MobileHash;		//0x460 + 0x20
			mmString MobileFullHash;    //0x480 + 0x20

			mmString ExtInfo;			//0x4A0 + 0x20

			mmString _0x4C0;		    //0x4C0 + 0x20

			mmString CardImgUrl;	    //0x4EO + 0x20

			char _res[0x1A8];           //0x500 + 
		};
	}
}


#endif // !_WECHAT_INNER_H
