#include "win_socket.h"

#include "win_util.h"

#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <utility>
#include <winsock2.h>

namespace acutis::net::windows {

Win_socket::Win_socket() {
	SPDLOG_TRACE("Default constructed Win_socket {}", socket_);
}

Win_socket::Win_socket(SOCKET socket) noexcept : socket_(socket)
{
	SPDLOG_TRACE("Constructed Win_socket with socket {}", socket_);
}

Win_socket::Win_socket(Win_socket&& other) noexcept
  : socket_(std::exchange(other.socket_, INVALID_SOCKET))
{
	SPDLOG_TRACE("Moved constructed Win_socket from socket {}", socket_);
}

Win_socket::~Win_socket()
{
	close();
	SPDLOG_TRACE("Destroyed Win_socket");
}

Win_socket& Win_socket::operator=(Win_socket&& other) noexcept
{
	socket_ = std::exchange(other.socket_, INVALID_SOCKET);
	SPDLOG_TRACE("Moved assigned Win_socket from socket {}", socket_);
	return *this;
}

void Win_socket::shutdown()
{
	int result = ::shutdown(socket_, SD_BOTH);
	if (result == SOCKET_ERROR) {
		wsa_log_last_error(fmt::format("Failed to shutdown socket {}:", socket_));
	}
}
void Win_socket::close()
{
	if (!is_open()) {
		return;
	}

	SPDLOG_INFO("Closing Win_socket {}", socket_);

	int result = ::closesocket(socket_);
	if (result == SOCKET_ERROR) {
		wsa_log_last_error(fmt::format("Failed to close socket {}: ", socket_));
	}
	socket_ = INVALID_SOCKET;
}

Win_socket create_win_socket()
{
	SOCKET s = ::socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		wsa_log_last_error("WSA create IP socket error");
	}
	return Win_socket(s);
}

}// namespace acutis::net::windows
