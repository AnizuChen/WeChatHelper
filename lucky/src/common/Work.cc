#include "Work.h"
#include <memory>

namespace lucky {

	namespace common {

		Work::Work() {

		}

		Work::~Work() {

		}

		void Work::CallBack(PTP_CALLBACK_INSTANCE instance, PVOID context,
			PTP_WORK w) {
			if (context == nullptr) {
				return;
			}
			std::unique_ptr<Work> ptr((Work*)context);
			ptr->Run();
		}


		ServiceWork::ServiceWork(void* context,
			const std::function<void(void*)>& onRequest,
			const std::function<void(void*)>& onResponse) {
			context_ = context;
			onRequest_ = onRequest;
			onResponse_ = onResponse;
		}
		
		ServiceWork::~ServiceWork() {}

		void ServiceWork::Run() {
			onRequest_(context_);
			onResponse_(context_);
		}
	}
}