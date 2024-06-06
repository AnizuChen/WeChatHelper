#include "EventLoop.h"

namespace lucky {
	namespace service {

		 bool mg_socketpair(MG_SOCKET_TYPE sp[2], union usa usa[2]) {
			socklen_t n = sizeof(usa[0].sin);
			bool success = false;

			sp[0] = sp[1] = MG_INVALID_SOCKET;
			(void)memset(&usa[0], 0, sizeof(usa[0]));
			usa[0].sin.sin_family = AF_INET;
			*(uint32_t*)&usa->sin.sin_addr = mg_htonl(0x7f000001U);  // 127.0.0.1
			usa[1] = usa[0];

			if ((sp[0] = socket(AF_INET, SOCK_DGRAM, 0)) != MG_INVALID_SOCKET &&
				(sp[1] = socket(AF_INET, SOCK_DGRAM, 0)) != MG_INVALID_SOCKET &&
				bind(sp[0], &usa[0].sa, n) == 0 &&          //
				bind(sp[1], &usa[1].sa, n) == 0 &&          //
				getsockname(sp[0], &usa[0].sa, &n) == 0 &&  //
				getsockname(sp[1], &usa[1].sa, &n) == 0 &&  //
				connect(sp[0], &usa[1].sa, n) == 0 &&       //
				connect(sp[1], &usa[0].sa, n) == 0) {       //
				success = true;
			}
			if (!success) {
				if (sp[0] != MG_INVALID_SOCKET) closesocket(sp[0]);
				if (sp[1] != MG_INVALID_SOCKET) closesocket(sp[1]);
				sp[0] = sp[1] = MG_INVALID_SOCKET;
			}
			return success;
		}



		EventLoop::EventLoop() {

			mgr_ = (struct mg_mgr*)malloc(sizeof(struct mg_mgr));

			if (mgr_) {

				memset((void*)mgr_, 0, sizeof(struct mg_mgr));
				mg_mgr_init(mgr_);

				if (this->pipe_ == MG_INVALID_SOCKET) {
					union usa usa[2];
					MG_SOCKET_TYPE sp[2] = { MG_INVALID_SOCKET, MG_INVALID_SOCKET };
					struct mg_connection* c = NULL;
					if (!mg_socketpair(sp, usa)) {
						MG_ERROR(("Cannot create socket pair"));
					}
					else if ((c = mg_wrapfd(this->mgr_, (int)sp[1], WakeFn, this)) == NULL) {
						closesocket(sp[0]);
						closesocket(sp[1]);
						sp[0] = sp[1] = MG_INVALID_SOCKET;
					}
					else {
						this->pipe_ = sp[0];
					}
				}
			}
		}

		EventLoop::~EventLoop() {
			mg_mgr_free(mgr_);
			if (mgr_) {
				free(mgr_);
			}
		}

		bool EventLoop::Wakeup(uint32_t conn_id, const char* buf, size_t len) {
			return mg_wakeup(this->mgr_, conn_id, buf, len);
		}

		uint32_t EventLoop::Wrapfd(int fd, EventHandler fn, void* fn_data) {
			struct mg_connection* c = NULL;
			c = mg_wrapfd(this->mgr_, fd, fn, fn_data);
			if (c != NULL) {
				return c->id;
			}
			return 0;
		}

		bool EventLoop::HttpListen(const std::string& host, EventHandler fn, void* fn_data) {
			return mg_http_listen(const_cast<mg_mgr*>(this->mgr_), host.c_str(), fn, fn_data) == NULL;
		}

		void EventLoop::WakeFn(struct mg_connection* c, int ev, void* ev_data) {
			OutputDebugString("EventLoop::WakeFn");
			if (ev == MG_EV_READ) {
				unsigned long* id = (unsigned long*)c->recv.buf;
				if (c->recv.len >= sizeof(*id)) {
						struct mg_connection* t;
						for (t = c->mgr->conns; t != NULL; t = t->next) {
							if (t->id == *id) {
								struct mg_str data = mg_str_n((char*)c->recv.buf + sizeof(*id),
									c->recv.len - sizeof(*id));
								mg_call(t, MG_EV_WAKEUP, &data);
							}
						}
				}
				c->recv.len = 0;  // Consume received data
			}
			else if (ev == MG_EV_CLOSE) {
				EventLoop* loop = (EventLoop*)ev_data;
				closesocket(loop->pipe_);         // When we're closing, close the other
				loop->pipe_ = MG_INVALID_SOCKET;  // side of the socketpair, too
			}
		}

		void EventLoop::LoopThread(EventLoop* e) {
			OutputDebugString("EventLoop Loop Start\n");
			while (e->running_.load(std::memory_order_acquire)) {
				mg_mgr_poll(const_cast<mg_mgr*>(e->mgr_), 100);
			}
			OutputDebugString("EventLoop Loop = false \n");
		}

		void EventLoop::Loop() {
			bool expected = false;
			bool desired = true;
			if (running_.compare_exchange_strong(expected, desired)) {
				HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LoopThread, this, NULL, 0);
				if (thread) {
					CloseHandle(thread);
				}
			}
		}

		void EventLoop::ShutDown() {
			running_.store(false, std::memory_order_release);
		}

	}
}