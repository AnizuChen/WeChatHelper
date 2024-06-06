#include "HttpClient.h"


namespace lucky {

	namespace service {


		struct RequestContext {
			RequestContext(const std::string& host,const std::string& message)
				:host(host), message(message) {}
			~RequestContext() {}
			std::string host;
			std::string message;
            int32_t timeout = 1500;
            std::atomic_bool done = false;
		};

        HttpClient::HttpClient(std::string host, int timeout)
            : host_(host), timeout_(timeout) {}

        void HttpClient::SendRequest(const std::string& message) {
            OutputDebugString("HttpClient::SendRequest");
            OutputDebugString(host_.c_str());
            struct mg_mgr mgr;
            RequestContext context(host_, message);
            mg_mgr_init(&mgr);
            mg_http_connect(&mgr, host_.c_str(), &HttpClient::fn, &context);
            while (!context.done) {
                mg_mgr_poll(&mgr, 200);
            }
            mg_mgr_free(&mgr);
            context.done = false;
        }

        void HttpClient::fn(struct mg_connection* c, int ev, void* ev_data) {
            RequestContext* context = (RequestContext*)c->fn_data;
            const char* s_url = context->host.c_str();
            int timeout = context->timeout;
            if (ev == MG_EV_OPEN) {
                // Connection created. Store connect expiration time in c->data
                *(uint64_t*)c->data = mg_millis() + timeout;
            }
            else if (ev == MG_EV_POLL) {
                if (mg_millis() > *(uint64_t*)c->data &&
                    (c->is_connecting || c->is_resolving)) {
                    mg_error(c, "Connect timeout");
                }
            }
            else if (ev == MG_EV_CONNECT) {
                struct mg_str host = mg_url_host(s_url);
                // Send request
                size_t content_length = context->message.size();
                mg_printf(c,
                    "POST %s HTTP/1.0\r\n"
                    "Host: %.*s\r\n"
                    "Content-Type: application/json\r\n"
                    "Content-Length: %d\r\n"
                    "\r\n",
                    mg_url_uri(s_url), (int)host.len, host.buf, content_length);
                mg_send(c, context->message.c_str(), content_length);
            }
            else if (ev == MG_EV_HTTP_MSG) {
                // Response is received. Print it
                // c->is_closing = 1;  // Tell mongoose to close this connection
                c->is_draining = 1;
                context->done = true;  // Tell event loop to stops
            }
            else if (ev == MG_EV_ERROR) {
                context->done = true;  // Error, tell event loop to stop
            }
            else if (ev == MG_EV_CLOSE) {
                if (!context->done) {
                    context->done = true;
                }
            }
        }
	}
}