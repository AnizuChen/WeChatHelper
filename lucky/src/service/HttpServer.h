#ifndef _HTTPSERVER_H
#define _HTTPSERVER_H

#include "mongoose.h"
#include <string>
#include <atomic>
#include <memory>
#include <map>
#include <functional>
#include <vector>
#include "utils/Singleton.h"

namespace lucky {
	namespace service {

		std::wstring GetWStringParam(const std::string data, std::string key);
		std::vector<std::wstring> GetArrayParam(const std::string data, std::string key);
		int GetIntParam(const std::string, std::string key);
		std::string GetStringParam(const std::string, std::string key);

		struct HttpContext {
			HttpContext(struct mg_mgr* mgr, 
				unsigned long conn_id,
				std::string&& message);
			~HttpContext();
			struct mg_mgr* mgr;
			unsigned long connID; 
			std::string request; 
			std::string response;
		};

		class HttpServer : public utils::Singleton<HttpServer> {
		public:
			HttpServer();
			~HttpServer();
			void Init(const std::string& host);
			void Start();
			void ShutDown();
			bool isRunning();
			std::string GetHost();
			const mg_mgr* GetMgr() { return mgr_; }
			static void LaunchServer(HttpServer* server);
			static void EventHandler(struct mg_connection* c, int ev, void* ev_data);
			static void HandleHttpMsg(struct mg_connection* c, void* ev_data,
				void* fn_data);
			void AddPathRoute(const std::string& path,
				std::function<std::string(const std::string&)> handler);
			std::function<void(void*)> FindPathRoute(const std::string& path);
		private:
			std::string		host_ = "";
			struct mg_mgr*	mgr_ = nullptr;
			std::atomic_bool running_{ false };
			std::map<std::string, std::function<void(void*)> > route_table_ = {};
		};
	}
}

#endif // !_HTTPSERVER_H
