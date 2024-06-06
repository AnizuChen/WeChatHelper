#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include "Work.h"
#include "utils/Singleton.h"
#include <windows.h>

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>


namespace lucky {

	namespace common  {

		class  ThreadPool : public utils::Singleton<ThreadPool> {
		public:
			ThreadPool();
			~ThreadPool();
			void Submit(Work *work); 
			bool Create(unsigned long size);
			void ShutDown();
		private:
			PTP_POOL pool_ = nullptr;
			PTP_CLEANUP_GROUP cleanup_group_ = nullptr;
			TP_CALLBACK_ENVIRON env_ ;
		};
	}
}

#endif // !_THREADPOOL_H