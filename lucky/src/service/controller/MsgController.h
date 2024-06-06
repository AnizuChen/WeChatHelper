#ifndef _MSGCONTROLLER_H
#define _MSGCONTROLLER_H

#include "HttpController.h"


namespace lucky {
	namespace service {
		namespace controller {

			class MsgController : public HttpController<MsgController> {
			public:
				PATHS_BEGIN
					ADD_PATH("/api/wechat/sendtextmsg", SendTextMsg);
					ADD_PATH("/api/wechat/sendimagemsg", SendImageMsg);
					ADD_PATH("/api/wechat/sendfilemsg", SendFileMsg);
					ADD_PATH("/api/wechat/sendpatmsg", SendPatMsg);
					ADD_PATH("/api/wechat/sendcardmsg", SendCardMsg);
					ADD_PATH("/api/wechat/setmessagenotify", SetMessageNotify);
				PATHS_END

			public:
				static std::string SendTextMsg(const std::string& params);
				static std::string SendImageMsg(const std::string& params);
				static std::string SendFileMsg(const std::string& params);
				static std::string SendPatMsg(const std::string& params);
				static std::string SendCardMsg(const std::string& params);

				static std::string SetMessageNotify(const std::string& params);
			};


		}
	}
}

#endif