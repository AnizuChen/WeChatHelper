#ifndef _WORK_H
#define _WORK_H

#include <windows.h>
#include <functional>

namespace lucky {

	namespace common {

		struct  Work
		{
			Work();
			virtual ~Work();
			virtual void Run() = 0;
			static void CallBack(PTP_CALLBACK_INSTANCE instance, PVOID context,
				PTP_WORK Work);
		};

		struct ServiceWork : public Work {
			ServiceWork(void *context,
				const std::function<void(void*)>& onRequest,
				const std::function<void(void*)>& onResponse);
			~ServiceWork();
			void Run();
			void* context_;
			std::function<void(void*)> onRequest_;
			std::function<void(void*)> onResponse_;
		};
	}
}


#endif // !_WORK_H
