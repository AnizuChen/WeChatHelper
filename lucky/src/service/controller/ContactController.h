#ifndef _CONTACTCONTROLLER_H
#define _CONTACTCONTROLLER_H

#include "HttpController.h"

namespace lucky {
	namespace service {
		namespace controller {

			class ContactController : public HttpController<ContactController> {
			public:
				PATHS_BEGIN
				ADD_PATH("/api/netscene/getcontact", NetSceneGetContact);
				ADD_PATH("/api/netscene/searchcontact", NetSceneSearchContact);
				ADD_PATH("/api/netscene/addcontact", NetSceneAddContact);
				ADD_PATH("/api/netscene/verifyapply", NetSceneVerifyApply);
				ADD_PATH("/api/netscene/getcontactlabellist", NetSceneGetContactLabelList);
				ADD_PATH("/api/netscene/addcontactlabel", NetSceneAddContactLabel);

				ADD_PATH("/api/wechat/delcontact", DelContact);
				ADD_PATH("/api/wechat/getcontact", GetContact);
				ADD_PATH("/api/wechat/getcontactlist", GetContactList);
				ADD_PATH("/api/wechat/remarkcontact", RemarkContact);
				ADD_PATH("/api/wechat/blackcontact", BlackContact);
				ADD_PATH("/api/wechat/delcontactlabel", DelContactLabel);
				ADD_PATH("/api/wechat/modifycontactlabel", ModifyContactLabel);

				PATHS_END

			public:
				static std::string NetSceneGetContact(const std::string& params);
				static std::string NetSceneSearchContact(const std::string& params);
				static std::string NetSceneAddContact(const std::string& params);
				static std::string NetSceneVerifyApply(const std::string& params);
				static std::string NetSceneGetContactLabelList(const std::string& params);
				static std::string NetSceneAddContactLabel(const std::string& params);


				static std::string DelContact(const std::string& params);
				static std::string GetContact(const std::string& params);
				static std::string GetContactList(const std::string& params);
				static std::string RemarkContact(const std::string& params);
				static std::string BlackContact(const std::string& params);

				static std::string DelContactLabel(const std::string& params);
				static std::string ModifyContactLabel(const std::string& params);
				

			};


		}
	}
}



#endif // !_CONTACTCONTROLLER_H
