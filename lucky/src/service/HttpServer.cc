#include "HttpServer.h"
#include "common/Work.h"
#include "common/Threadpool.h"
#include "utils/Utils.h"

namespace lucky {
	namespace service {

		std::wstring GetWStringParam(const std::string data, std::string key) {
			const char *v =  mg_json_get_str(mg_str(data.c_str()), key.c_str());
			return utils::Utf8ToWstring(std::string(v));
		}
		std::vector<std::wstring> GetArrayParam(const std::string data, std::string key) {
			std::vector<std::wstring> result;
			std::wstring param = GetWStringParam(data, key);
			result = utils::split(param, L',');
			return result;
		}
		int GetIntParam(const std::string data, std::string key) {
			return mg_json_get_long(mg_str(data.c_str()), key.c_str(),0);
		}
		std::string GetStringParam(const std::string data, std::string key) {
			const char* v = mg_json_get_str(mg_str(data.c_str()), key.c_str());
			return v;
		}

		HttpContext::HttpContext(struct mg_mgr* mgr,
			unsigned long connID,
			std::string&& request):mgr(mgr), connID(connID),
			request(std::move(request)),response("") {}

		HttpContext::~HttpContext() {}

		HttpServer::HttpServer(){
			mgr_ = (struct mg_mgr*)malloc(sizeof(struct mg_mgr));
			if (mgr_) {
				memset((void*)mgr_, 0, sizeof(struct mg_mgr));
				mg_mgr_init(mgr_);
				mg_wakeup_init(mgr_);
			}
		}

		HttpServer::~HttpServer() {
			mg_mgr_free(mgr_);
			if (mgr_) {
				free(mgr_);
			}
		}
		void HttpServer::AddPathRoute(const std::string& path,
			std::function<std::string(const std::string&)> handler) {
			route_table_[path] = [handler](void* context) {
				if (context == nullptr) {
					return;
				}
				HttpContext* c = (HttpContext*)context;
				c->response = std::move(handler(c->request));
			};
		}
		std::function<void(void*)> HttpServer::FindPathRoute(const std::string& path) {
			auto  onReqeust = route_table_.find(path);
			if (onReqeust == route_table_.end()) {
				return nullptr;
			}
			return onReqeust->second;
		}

		void HttpServer::HandleHttpMsg(struct mg_connection* c, void* ev_data, void* fn_data) {
			struct mg_http_message* hm = (struct mg_http_message*)ev_data;
			std::string method(hm->method.buf, hm->method.len);
			if (mg_strcasecmp(hm->method, mg_str("GET")) == 0) {
				std::string response = R"({"code":200,"msg":"the get method is not supported.please use post method."})";
				mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\n",
					response.c_str());
				return;
			}
			else if (mg_strcasecmp(hm->method, mg_str("POST")) == 0) {
				std::string url(hm->uri.buf, hm->uri.len);
				auto  onReqeust = HttpServer::GetInstance().FindPathRoute(url);
				if (onReqeust == nullptr) {
					std::string response = R"({"code":200,"msg":"the url is not supported."})";
					mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\n",
						response.c_str());
					return;
				}	
				std::string request = "{}";
				if (hm->body.len > 0) {
					request = std::string(hm->body.buf, hm->body.len);
				}
				HttpContext* context = new HttpContext(c->mgr, c->id, std::move(request));
				common::Work* work = new common::ServiceWork(
					(void*)context,
					onReqeust,
					[](void* context) {
						if (context == nullptr) {return;}
						HttpContext * c = (HttpContext*)context;
						mg_wakeup(c->mgr, c->connID, &c , sizeof(void*));
					});
				common::ThreadPool::GetInstance().Submit(work);
			}
		}
		void HttpServer::EventHandler(struct mg_connection* c, int ev, void* ev_data) {
			if (ev == MG_EV_HTTP_MSG) { 
				OutputDebugString("HttpServer::EventHandler MG_EV_HTTP_MSG\n");
				struct mg_http_message* hm = (struct mg_http_message*)ev_data;
				std::string url(hm->uri.buf, hm->uri.len);
				struct mg_str caps[3];
				if (mg_match(hm->uri, mg_str("/api/*/*"), caps)) {
					HandleHttpMsg(c, hm, ev_data);
				}
				else {
					std::string response = R"({"code":400,"msg":"invalid url, please check url"})";
					mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\n", response.c_str());
				}
			}else if (ev == MG_EV_WAKEUP) {
				OutputDebugString("HttpServer::EventHandler MG_EV_WAKEUP\n");
				struct mg_str* data = (struct mg_str*)ev_data;
				uint64_t addr = *(uint64_t*)data->buf;
				std::unique_ptr<HttpContext> context((HttpContext*)addr);
				if (context == nullptr) { return; }
				mg_http_reply(c, 200, "Content-Type: application/json\r\n", "%s\n",
					context->response.c_str());
			}
		}
		void HttpServer::LaunchServer(HttpServer* server) {
			std::string host = server->GetHost();
			const mg_mgr* mgr = server->GetMgr();
			if (mg_http_listen(const_cast<mg_mgr*>(mgr), host.c_str(), EventHandler, NULL) == NULL) {
				return;
			}
			OutputDebugString("HttpServer Poll Start\n");
			while (server->isRunning()) {
				mg_mgr_poll(const_cast<mg_mgr*>(mgr), 100);
			}
			OutputDebugString("HttpServer isRunning = false \n");	
		}

		void HttpServer::Init(const std::string& host) {
			host_ = host;
		}

		bool HttpServer::isRunning() {
			return running_.load(std::memory_order_acquire);
		}

		void HttpServer::Start() {
			
			bool expected = false;
			bool desired = true;
			if (running_.compare_exchange_strong(expected, desired)) {
				HANDLE thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)LaunchServer, this, NULL, 0);
				if (thread) {
					CloseHandle(thread);
				}
			}
		}
		void HttpServer::ShutDown() {
			running_.store(false, std::memory_order_release);
		}
		std::string HttpServer::GetHost() {
			return host_;
		} 
	}
}
