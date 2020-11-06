#include "win_socket_api.h"
#include "win_util.h"
#include <fmt/core.h>
#include <mutex>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <winsock2.h>

namespace acutis::net::windows::internal {
namespace {
	constexpr WORD low_byte_mask = 0xff;
	constexpr uint8_t high_byte_shift = 8;

	constexpr BYTE wsa_major = 2;
	constexpr BYTE wsa_minor = 0;
	constexpr WORD wsa_req_version = MAKEWORD(wsa_major, wsa_minor);

	std::once_flag init_flag;
}// namespace


void Win_socket_api::initialize()
{
	std::call_once(init_flag, do_initialize);
}

void Win_socket_api::do_initialize()
{
	WSADATA wsa_data;
	int result = WSAStartup(wsa_req_version, &wsa_data);
	if (result != 0) {
		throw std::runtime_error(
			fmt::format("Failure to initialize Windows Sockets v {}.{}", wsa_major, wsa_minor));
	}

	auto high = (wsa_data.wVersion >> high_byte_shift) & low_byte_mask;
	auto low = wsa_data.wVersion & low_byte_mask;
	spdlog::get("acutis")->info("Initialized WSA v{0}.{1}", high, low);
}

void Win_socket_api::cleanup()
{
	int result = WSACleanup();
	if (result == 0) {
		spdlog::get("acutis")->info("WSA Cleanup successful");
	} else {
		const int error = WSAGetLastError();
		const std::string error_msg = error_message(error);
		spdlog::get("acutis")->error("WSA Cleanup error {}: {}", error, error_msg);
	}
}

}// namespace acutis::net::windows::internal
