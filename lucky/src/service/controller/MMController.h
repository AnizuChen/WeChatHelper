#ifndef _MMCONTROLLER_H
#define _MMCONTROLLER_H

#include "HttpController.h"


namespace lucky {
	namespace service {
		namespace controller {

			class MMController : public HttpController<MMController> {
			public:
				PATHS_BEGIN
				ADD_PATH("/api/netscene/getA8key", NetSceneGetA8Key);
				ADD_PATH("/api/wechat/cdndownload", CdnDownload);  
				ADD_PATH("/api/wechat/cdnupload", CdnUpload);
				ADD_PATH("/api/wechat/getselfinfo", GetSelfInfo);
				ADD_PATH("/api/wechat/wxdump", WxDump);
				PATHS_END

			public:
				static std::string NetSceneGetA8Key(const std::string& params);
				//文件下载还未实现
				static std::string CdnDownload(const std::string& params);
				//TODO
				static std::string CdnUpload(const std::string& params);
				//微信协议dump (TODO)
				static std::string WxDump(const std::string& params);

				static std::string GetSelfInfo(const std::string& params);
			};


		}
	}
}

#endif