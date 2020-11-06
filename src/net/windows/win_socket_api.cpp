#include "win_socket_api.h"
#include "win_util.h"
#include <fmt/core.h>
#include <mutex>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <string_view>
#include <winsock2.h>

namespace acutis::net::windows::internal {
namespace {
	constexpr BYTE wsa_major = 2;
	constexpr BYTE wsa_minor = 0;
	constexpr WORD wsa_req_version = MAKEWORD(wsa_major, wsa_minor);

	std::once_flag wsa_init_flag;
	std::once_flag wsa_cleanup_flag;

	int wsa_log_last_error(std::string_view msg)
	{
		const int error = WSAGetLastError();
		const std::string error_msg = error_message(error);
		spdlog::get("acutis")->error("{} {}: {}", msg, error, error_msg);
		return error;
	}

}// namespace


void wsa_initialize()
{
	std::call_once(wsa_init_flag, []() {
		WSADATA wsa_data;
		int result = WSAStartup(wsa_req_version, &wsa_data);
		if (result != 0) {
			wsa_log_last_error("WSA Cleanup error");
			throw std::runtime_error(
				fmt::format("Failure to initialize Windows Sockets v{}.{}", wsa_major, wsa_minor));
		}

		spdlog::get("acutis")->info(
			"Initialized WSA v{}.{}", HIBYTE(wsa_data.wHighVersion), LOBYTE(wsa_data.wHighVersion));
	});
}

void wsa_cleanup()
{
	std::call_once(wsa_cleanup_flag, []() {
		int result = WSACleanup();
		if (result == 0) {
			spdlog::get("acutis")->info("WSA Cleanup successful");
		} else {
			wsa_log_last_error("WSA Cleanup error");
		}
	});
}


}// namespace acutis::net::windows::internal
