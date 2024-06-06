#include "Service.h"
#include "common/Threadpool.h"
#include "controller/HttpController.h"
#include "controller/ContactController.h"
#include "controller/MsgController.h"
#include "controller/ChatRoomController.h"
#include "controller/MMController.h"
#include "controller/SnsController.h"
#include "EventLoop.h"

namespace lucky {
	namespace service {

		using namespace lucky::service::controller;
		using namespace lucky::common;

		Service::Service(){
			HttpServer::GetInstance().Init("http://127.0.0.1:9527");
			ContactController::GetInstance();
			MsgController::GetInstance();
			ChatRoomController::GetInstance();
			MMController::GetInstance();
			SNSController::GetInstance();
		}

		Service::~Service() {
			OutputDebugString("~Service \n");
		}

		bool Service::Start() {
			OutputDebugString("Service::Start ENTER \n");
			bool expected = false;
			bool desired = true;
			if (running_.compare_exchange_strong(expected, desired)) {
				ThreadPool::GetInstance().Create(4);
				HttpServer::GetInstance().Start();
				OutputDebugString("Service::Start OK \n");
			}
			return true;
		}

		bool Service::ShutDown() {
			OutputDebugString("Service::ShutDown START\n");
			bool expected = true;
			bool desired = false;
			if (running_.compare_exchange_strong(expected, desired)) {
				HttpServer::GetInstance().ShutDown();
				ThreadPool::GetInstance().ShutDown();
			}
			OutputDebugString("Service::ShutDown END \n");
			return true;
		}
	}
}