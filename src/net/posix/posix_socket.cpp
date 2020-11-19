#include "posix_socket.h"

#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <utility>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "posix_util.h"

namespace acutis::net {

Posix_socket::Posix_socket() {
	SPDLOG_TRACE("Default constructed Posix_socket {}", socket_);
}

Posix_socket::Posix_socket(int socket) noexcept : socket_(socket)
{
	SPDLOG_TRACE("Constructed Posix_socket with socket {}", socket_);
}

Posix_socket::Posix_socket(Posix_socket&& other) noexcept
  : socket_(std::exchange(other.socket_, INVALID_SOCKET))
{
	SPDLOG_TRACE("Moved constructed Posix_socket from socket {}", socket_);
}

Posix_socket::~Posix_socket()
{
	close();
	SPDLOG_TRACE("Destroyed Posix_socket");
}

Posix_socket& Posix_socket::operator=(Posix_socket&& other) noexcept
{
	socket_ = std::exchange(other.socket_, INVALID_SOCKET);
	SPDLOG_TRACE("Moved assigned Posix_socket from socket {}", socket_);
	return *this;
}

void Posix_socket::shutdown()
{
}
void Posix_socket::close()
{
	if (!is_open()) {
		return;
	}

	SPDLOG_INFO("Closing Posix_socket {}", socket_);

	int result = ::close(socket_);
	if (result == -1) {
		posix_log_last_error(fmt::format("Failed to close socket {}: ", socket_));
	}
	socket_ = INVALID_SOCKET;
}

Posix_socket create_posix_socket()
{
	int s = ::socket(AF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		posix_log_last_error("Posix create IP socket error");
	}
	return Posix_socket(s);
}

}// namespace acutis::net
