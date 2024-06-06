#ifndef _SNSCONTROLLER_H
#define _SNSCONTROLLER_H

#include "HttpController.h"


namespace lucky {
	namespace service {
		namespace controller {

			class SNSController : public HttpController<SNSController> {
			public:
				PATHS_BEGIN
			    ADD_PATH("/api/netscene/timelinegetfirstpage", NetSceneTimelineGetFirstPage);
				ADD_PATH("/api/netscene/timelinegetnextpage", NetSceneTimelineGetNextPage);
				ADD_PATH("/api/netscene/snsobjectdetail", NetSceneSnsObjectDetail);

				ADD_PATH("/api/wechat/snsobjectlike", SnsObjectLike);
				ADD_PATH("/api/wechat/snsobjectunlike", SnsObjectUnLike);

				ADD_PATH("/api/wechat/snsobjectdocomment", SnsObjectDoComment);
				ADD_PATH("/api/wechat/snsobjectdelcomment", SnsObjectDelComment);
				PATHS_END

			public:
				static std::string NetSceneTimelineGetFirstPage(const std::string& params);
				static std::string NetSceneTimelineGetNextPage(const std::string& params);
				static std::string NetSceneSnsObjectDetail(const std::string& params);

				static std::string SnsObjectLike(const std::string& params);
				static std::string SnsObjectUnLike(const std::string& params);

				static std::string SnsObjectDoComment(const std::string& param);
				static std::string SnsObjectDelComment(const std::string& param);
			};


		}
	}
}
#endif