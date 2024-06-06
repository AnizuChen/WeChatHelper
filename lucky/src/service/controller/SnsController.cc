#include "SnsController.h"
#include "utils/Utils.h"
#include <vector>
#include "wechat/NetScene.h"
#include "wechat/WeChat.h"
#include <google/protobuf/util/json_util.h>
#include "SnsTimeLineResponse.pb.h"
#include <sstream>

namespace lucky {
	namespace service {
		namespace controller {
			using namespace MMPro::micromsg;
			using namespace google::protobuf::util;

			 std::string SNSController::NetSceneTimelineGetFirstPage(const std::string& params) {
				 std::shared_ptr<SnsTimeLineResponse> result = lucky::wechat::NetScence::GetInstance().TimelineGetFirstPage();
				 std::string response = R"({"code":200,"msg":"NetSceneTimelineGetFirstPage."})";
				 if (result != nullptr) {
					 response = "";
					 MessageToJsonString(*result.get(), &response);
				 }
				 return response;
			 }

			 std::string SNSController::NetSceneTimelineGetNextPage(const std::string& params) {
				 std::string id = GetStringParam(params, "$.id");
				 std::shared_ptr<SnsTimeLineResponse> result = lucky::wechat::NetScence::GetInstance().TimelineGetNextPage(id);
				 std::string response = R"({"code":200,"msg":"NetSceneTimelineGetNextPage."})";
				 if (result != nullptr) {
					 response = "";
					 MessageToJsonString(*result.get(), &response);
				 }
				 return response;
			 }

			 std::string SNSController::NetSceneSnsObjectDetail(const std::string& params) {
				 std::string id = GetStringParam(params, "$.id");
				 std::shared_ptr<SnsObjectDetailResponse> result = lucky::wechat::NetScence::GetInstance().SnsObjectDetail(id);
				 std::string response = R"({"code":200,"msg":"NetSceneSnsObjectDetail."})";
				 if (result != nullptr) {
					 response = "";
					 MessageToJsonString(*result.get(), &response);
				 }
				 return response;
			 }

			 std::string SNSController::SnsObjectLike(const std::string& params) {
				 std::string  id = GetStringParam(params, "$.id");
				 std::wstring  wxid = GetWStringParam(params, "$.wxid");
				 uint64_t  success = lucky::wechat::WeChat().SnsObjectLike(id, wxid);
				 std::ostringstream oss;
				 oss << "{\"code\":" << success << "}";
				 return oss.str();
			 }

			 std::string SNSController::SnsObjectUnLike(const std::string& params) {
				 std::string  id = GetStringParam(params, "$.id");
				 uint64_t  success = lucky::wechat::WeChat().SnsObjectUnLike(id);
				 std::ostringstream oss;
				 oss << "{\"code\":" << success << "}";
				 return oss.str();
			 }

			 std::string SNSController::SnsObjectDoComment(const std::string& param) {
				 std::string  id = GetStringParam(param, "$.id");
				 std::wstring  comment = GetWStringParam(param, "$.comment");
				 uint64_t  success = lucky::wechat::WeChat().SnsObjectDoComment(id, comment);
				 std::ostringstream oss;
				 oss << "{\"code\":" << success << "}";
				 return oss.str();
			 }

			 std::string SNSController::SnsObjectDelComment(const std::string& param) {
				 std::string  id = GetStringParam(param, "$.id");
				 uint32_t commentId = GetIntParam(param, "$.commentId");
				 uint64_t  success = lucky::wechat::WeChat().SnsObjectDelComment(id, commentId);
				 std::ostringstream oss;
				 oss << "{\"code\":" << success << "}";
				 return oss.str();
			 }

		}
	}
}

