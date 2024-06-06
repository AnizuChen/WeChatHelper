#include "ThreadPool.h"


namespace lucky {
	namespace common {

		ThreadPool::ThreadPool() {
			InitializeThreadpoolEnvironment(&env_);
		}

		ThreadPool::~ThreadPool() {
			
		}

		bool ThreadPool::Create(unsigned long size) {
			pool_ = CreateThreadpool(NULL);
			if (NULL == pool_) {
				return false;
			}
			SetThreadpoolThreadMaximum(pool_, size*2);
			BOOL ret = SetThreadpoolThreadMinimum(pool_, size);
			if (FALSE == ret) {
				return false;
			}
			cleanup_group_ = CreateThreadpoolCleanupGroup();
			if (NULL == cleanup_group_) {
				return false;
			}
			SetThreadpoolCallbackPool(&env_, pool_);
			SetThreadpoolCallbackCleanupGroup(&env_, cleanup_group_, NULL);
			return true;
		}

		void ThreadPool::ShutDown() {
			OutputDebugString("ThreadPool::ShutDown \n");
			if (cleanup_group_) {
				CloseThreadpoolCleanupGroupMembers(cleanup_group_, true, NULL);
				CloseThreadpoolCleanupGroup(cleanup_group_);
			}
			DestroyThreadpoolEnvironment(&env_);
			if (pool_) {
				CloseThreadpool(pool_);
			}
			OutputDebugString("ThreadPool::ShutDown END \n");
		}

		void ThreadPool::Submit(Work* work) {
			PTP_WORK pt = CreateThreadpoolWork(Work::CallBack, (PVOID)work, &env_);
			if (pt == nullptr) {
				return ;
			}
			SubmitThreadpoolWork(pt);
		}
	}
}