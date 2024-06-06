#include "VTableHook.h"
#include <windows.h>
#include <sstream>

namespace lucky {
	namespace wechat {
		VFunction::VFunction():o(0),n(0) {}
		VFunction::VFunction( uint64_t o, uint64_t n) :o(o), n(n) {}
		VFunction::~VFunction() {}

		VTableHook::VTableHook() {}
		VTableHook::~VTableHook() {}

		uint64_t VTableHook::Hook(uint64_t* addr, uint64_t n) {
			std::lock_guard<std::mutex> lock(_mutex);
			auto it = hook_map_.find(addr);
			if (it != hook_map_.end()) {
				return it->second.o;
			}
			//HOOK
			uint64_t old = *addr;
			DWORD oldProtect;
			VirtualProtect(addr, sizeof(uint64_t), PAGE_EXECUTE_READWRITE, &oldProtect);
			*addr = n;
			VirtualProtect(addr, sizeof(uint64_t), oldProtect, &oldProtect);
			hook_map_[addr]  = VFunction(old, n);
			return old;
		}

		//获取原本的虚函数
		uint64_t VTableHook::GetHook(uint64_t* addr) {
			std::lock_guard<std::mutex> lock(_mutex);
			auto it = hook_map_.find(addr);
			if (it != hook_map_.end()) {
				return it->second.o;
			}
			//这里要报错的
			return 0;
		}

		//恢复
		void  VTableHook::ShutDown() {
			std::lock_guard<std::mutex> lock(_mutex);
			OutputDebugString("VTableHook::ShutDown \n");
			for (const auto& pair : hook_map_) {
				DWORD oldProtect;
				VirtualProtect(pair.first, sizeof(uint64_t), PAGE_EXECUTE_READWRITE, &oldProtect);
				*pair.first = pair.second.o;
				std::stringstream s2;
				s2 << "VTableHook::ShutDown  " << std::hex << pair.first << ":" << std::hex << pair.second.o << std::endl;
				OutputDebugString(s2.str().c_str());
				VirtualProtect(pair.first, sizeof(uint64_t), oldProtect, &oldProtect);
			}
			hook_map_.clear();
		}

	

		
	}
}