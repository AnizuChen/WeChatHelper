#include "CallBack.h"
#include "CallBackManager.h"
#include <sstream>
#include "VTableHook.h"

namespace lucky {

	namespace wechat {

		CallBack::CallBack() {

		}

		CallBack::~CallBack() {
			OutputDebugString("~CallBack");
		}

		uint64_t CallBack::OnNetRespone(uint64_t a1, int32_t a2, int32_t a3, uint64_t a4, int32_t a5) {
			return 0;
		}

		uint64_t CallBack::OnNetResponeHookProxy(uint64_t a1, int32_t a2, int32_t a3, uint64_t a4, int32_t a5) {
			OutputDebugString("OnNetResponeHookProxy");
			auto result = this->OnNetRespone(a1, a2, a3, a4, a5);
			OutputDebugString("OnNetResponeHookProxy OnNetRespone");
			if (_OnNetRespone) {
				OutputDebugString("OnNetResponeHookProxy _OnNetRespone");
				return _OnNetRespone(a1,a2,a3,a4,a5);
			}
			return result;
		}

		void CallBack::SetSeqID(uint32_t seqID) {
			_seqID = seqID;
			std::shared_ptr<CallBack> ptr = shared_from_this();
			CallBackManager::GetInstance().Add(_seqID, ptr);
		}
		uint32_t CallBack::GetSeqID() {
			return _seqID;
		}

		void CallBack::HookOnNetRespone(uint64_t* a2){
			
			//一个线程里面两次调用网络请求
			if (_seqID != 0) {
				std::ostringstream oss;
				oss << "CallBack::HookOnNetRespone Secord  :" << _seqID;
				OutputDebugString(oss.str().c_str());
				return;
			}

			uint32_t* ptr = reinterpret_cast<uint32_t*>(*a2 + 0x240);

			if (ptr != nullptr) {
				_seqID = *ptr; //seqID
			}

			std::ostringstream oss;
			oss << "CallBack::HookOnNetRespone:" << _seqID;
			OutputDebugString(oss.str().c_str());

			SetSeqID(_seqID);

			uint64_t* vptr = *reinterpret_cast<uint64_t**>(*a2);

			_OnNetRespone = (__OnNetRespone)VTableHook::GetInstance().Hook(&vptr[9],
				reinterpret_cast<uint64_t>(&this->OnNetResponeHook));

			OutputDebugString("HOOK OnNetResponeHook Success");

		}

		uint64_t CallBack::OnNetResponeHook(uint64_t a1, int32_t a2, int32_t a3, uint64_t a4, int32_t a5) {
		
			uint32_t seqID = *(uint32_t*)(a1 + 0x240);

			std::ostringstream oss;
			oss << "CallBack::OnNetResponeHook:" << seqID ;
			OutputDebugString(oss.str().c_str());

			std::shared_ptr<CallBack> callback = CallBackManager::GetInstance().Get(seqID);
			if (callback != nullptr) {
				OutputDebugString("OnNetResponeHook CALLBACK");
				return callback->OnNetResponeHookProxy(a1, a2, a3, a4, a5);
			}
			else {
				uint64_t* vptr = *reinterpret_cast<uint64_t**>(a1);
				OutputDebugString("OnNetResponeHook callback empty");
				__OnNetRespone OnNetRespone = (__OnNetRespone)VTableHook::GetInstance().GetHook(&vptr[9]);
				return OnNetRespone(a1, a2, a3, a4, a5);
			}
			return 0;
		}

		CallBackAutoTLS::CallBackAutoTLS(const std::shared_ptr<CallBack>& p) {
			if (GetTlsIndex() != TLS_OUT_OF_INDEXES) {
				TlsSetValue(GetTlsIndex(), (LPVOID)(&p));
			}
		}

		CallBackAutoTLS::~CallBackAutoTLS() {
			if (GetTlsIndex() != TLS_OUT_OF_INDEXES) {
				std::shared_ptr<CallBack> callback = GetCallBack();
				if (callback != nullptr) {
					CallBackManager::GetInstance().Remove(callback->GetSeqID());
				}
				TlsSetValue(GetTlsIndex(), nullptr);
			}
		}
		std::shared_ptr<CallBack> CallBackAutoTLS::GetCallBack() {
			if (GetTlsIndex() != TLS_OUT_OF_INDEXES) {
				LPVOID ptr = TlsGetValue(GetTlsIndex());
				if (ptr != nullptr) {
					return *(std::shared_ptr<CallBack>*)(ptr);
				}
			}
			return std::shared_ptr<CallBack>(0);
		}

		DWORD CallBackAutoTLS::GetTlsIndex() {
			if (tlsIndex == TLS_OUT_OF_INDEXES) {
				tlsIndex = TlsAlloc();
			}
			return tlsIndex;
		}

		DWORD CallBackAutoTLS::tlsIndex = TLS_OUT_OF_INDEXES;

	}
}

