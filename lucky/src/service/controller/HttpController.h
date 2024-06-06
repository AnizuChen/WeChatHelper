#ifndef _HTTPCONTROLLE_H
#define _HTTPCONTROLLE_H

#include "utils/Singleton.h"
#include "service/HttpServer.h"

namespace lucky {

	namespace service {

		namespace controller {

#define PATHS_BEGIN static void AddPath() {
#define ADD_PATH(path, method) RegisterPath(path, &method)
#define PATHS_END }

			template <typename T>
			class HttpController : public utils::Singleton<T> {
			public:
				virtual ~HttpController() {}

			protected:
				HttpController() {}

				static void RegisterPath(const std::string& path,
					std::function<std::string(const std::string&)> function) {
					HttpServer::GetInstance().AddPathRoute(path, function);
				}

			private:
				struct Registrator {
				public:
					Registrator() {
						T::AddPath();
					}
				};

				static Registrator registrator_;
				virtual void* GetRegistrator() { return &registrator_; }
			};

			template <typename T>
			typename HttpController<T>::Registrator HttpController<T>::registrator_;
		}
	}
}

#endif // !_HTTPCONTROLLE_H
