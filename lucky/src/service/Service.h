#ifndef _SERVICE_H_
#define _SERVICE_H_

#include<windows.h>
#include <atomic>
#include <utils/Singleton.h>
#include "HttpServer.h"

namespace lucky {

	namespace service  {

		struct Service : public utils::Singleton<Service> {
			Service();
			~Service();
			bool Start();
			bool ShutDown();
		private:
			std::atomic_bool running_{ false };
		};

	};
}

#endif