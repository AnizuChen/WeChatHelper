#ifndef _VTABLE_HOOK_H
#define _VTABLE_HOOK_H

#include "utils/Singleton.h"
#include <map>
#include <mutex>

namespace lucky {
	namespace wechat{

		struct VFunction {
			VFunction();
			VFunction( uint64_t o, uint64_t n);
			~VFunction();
			uint64_t	o; //¾Éº¯Êý
			uint64_t	n; //ÐÂº¯Êý
		};

		class VTableHook : public utils::Singleton<VTableHook>{
		public:
			VTableHook();
			~VTableHook();
			uint64_t Hook(uint64_t* addr, uint64_t n);
			uint64_t GetHook(uint64_t* addr);
			void ShutDown();
		private:
			std::mutex _mutex;
			std::map<uint64_t*, VFunction> hook_map_;
		};
	}
}

#endif // !_VTABLE_HOOK_H
