#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H

#include "utils/Singleton.h"
#include "mongoose.h"
#include <string>
#include <atomic>

namespace lucky {
	namespace service  {

		union usa {
			struct sockaddr sa;
			struct sockaddr_in sin;
		};

		bool mg_socketpair(MG_SOCKET_TYPE sp[2], union usa usa[2]);

		using EventHandler = void(struct mg_connection* c, int ev, void* data);
	
		struct EventLoop : public utils::Singleton<EventLoop> {

			EventLoop();
			~EventLoop();
			void Loop();

			static void LoopThread(EventLoop* e);

			void ShutDown();

			static void WakeFn(struct mg_connection* c, int ev, void* ev_data);

			bool Wakeup(uint32_t conn_id, const char* buf, size_t len);

			uint32_t Wrapfd(int fd, EventHandler fn, void* fn_data);

			bool HttpListen(const std::string& host, EventHandler fn, void* fn_data);

			struct mg_mgr* mgr_ = nullptr;
			std::atomic_bool running_{ false };

			MG_SOCKET_TYPE pipe_ = MG_INVALID_SOCKET;          // Socketpair end for mg_wakeup()
		};
	}
}


#endif // !_EVENTLOOP_H
