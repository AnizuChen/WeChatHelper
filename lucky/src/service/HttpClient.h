#ifndef _HTTPCLIENT_H
#define _HTTPCLIENT_H

#include <string>
#include <functional>
#include <map>
#include <mutex>

#include "mongoose.h"

namespace lucky {

	namespace service {


		class HttpClient {
		public:
			HttpClient(std::string url, int timeout = 1500);
			void SendRequest(const std::string& message);
		private:
			static void fn(struct mg_connection*, int ev, void* ev_data);

		private:
			std::string host_;
			int timeout_;
		};


	}
}

#endif // !_HTTPCLIENT_H
