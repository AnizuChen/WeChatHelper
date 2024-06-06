#ifndef _NETSCENECALLBACK_H
#define _NETSCENECALLBACK_H

#include "CallBack.h"
#include <chrono>
#include <future>
#include <windows.h>
#include <google/protobuf/message.h>
#include <sstream>
#include <google/protobuf/text_format.h>

namespace lucky {
	namespace wechat {
		template<typename T>
		class NetSceneCallBack : public CallBack {
		public:

			uint64_t OnNetRespone(uint64_t a1, int32_t a2, int32_t a3, uint64_t a4, int32_t a5) {
				//Э�����
				OutputDebugString("OnNetRespone ENTER\n");
				uint64_t v25 = *(uint64_t*)(a1 + 0x300);

				/*
				const WCHAR* v24 = *(const WCHAR**)(a1 + 0x320);
				int len = *(DWORD*)(a1 + 0x328);
				std::wstring v(v24, len);
				OutputDebugStringW(L"v24\n");
				OutputDebugStringW(v.c_str()); */
	

		    //  ΢�������õ���pb 2.5.0   message+0x40 ��ByteSize()
			//	google::protobuf::MessageLite* message = (google::protobuf::MessageLite*)v25;
			//	int size = message->ByteSize();
			//  uint8_t* data = new uint8_t[size];
		    //  message->SerializeWithCachedSizesToArray(data);

				int size = (*(uint64_t(__fastcall**)(uint64_t))(*(uint64_t*)v25 + 0x40))(v25);// ���ݰ�����

				std::stringstream s2;
				s2 << "onNetResponse ByteSize: " << size;

				OutputDebugString(s2.str().c_str());
				uint8_t* data = new uint8_t[size];

				(*(uint64_t(__fastcall**)(uint64_t, uint64_t))(*(uint64_t*)v25 + 0x50))(v25, (uint64_t)data);

				google::protobuf::Message* response = new T();
				response->ParseFromArray(data, size);	
				delete[] data;

				OutputDebugString("ParseFromArray OK\n");
	
				_prom.set_value(std::shared_ptr<T>((T*)response));
				return 0;
			}

			std::shared_ptr<T> WaitFor(std::chrono::milliseconds timeout) {
				auto  fut = _prom.get_future();
				if (fut.wait_for(timeout) == std::future_status::ready) {
					OutputDebugString("GET Ready");
					return  fut.get();
				}
				else {
					// ��ʱδ��ȡ�����
				//	LOG_WARN << "Timeout, No result";
				}
				return std::shared_ptr<T>(0);
			}
		private:
			std::promise< std::shared_ptr<T> >	_prom;
		};

	}
}

#endif