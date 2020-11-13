#include "win_server_socket.h"

#include "win_util.h"

#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <winsock2.h>

namespace acutis::net::windows {

Win_server_socket::Win_server_socket(Win_socket&& socket) : socket_(std::move(socket))
{
	SPDLOG_TRACE("Constructed server socket from socket {}", socket_.socket());
}

Win_server_socket::Win_server_socket(Win_server_socket&& other) noexcept
  : socket_(std::move(other.socket_))
{
	SPDLOG_TRACE("Moved constructed server socket {}", socket_.socket());
}

Win_server_socket::~Win_server_socket()
{
	close();
	SPDLOG_TRACE("Destroyed Socket_server");
}

Win_server_socket& Win_server_socket::operator=(Win_server_socket&& other) noexcept
{
	socket_ = std::move(other.socket_);
	SPDLOG_TRACE("Moved assigned server socket {}", socket_);
	return *this;
}

void Win_server_socket::close()
{
	SPDLOG_INFO("Closing server socket {}", socket_.socket());

	socket_.close();
}

Win_server_socket create_win_server_socket()
{
	return Win_server_socket( create_win_socket() );
}

void Win_server_socket::bind(Address address, uint16_t port)
{
	sockaddr_in sa{};
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(address.to_ulong());
	sa.sin_port = htons(port);

	int result = ::bind(socket_.socket(), reinterpret_cast<sockaddr*>(&sa), sizeof(sa));
	if (result == SOCKET_ERROR) {
		wsa_log_last_error("WSA error binding socket");
		throw std::runtime_error(fmt::format("WSA error binding socket {}", socket_.socket()));
	}
	SPDLOG_INFO("Bound socket {} on {}:{}", socket_.socket(), address.to_string(), port);
}

void Win_server_socket::listen()
{
	int result = ::listen(socket_.socket(), SOMAXCONN);
	if (result == SOCKET_ERROR) {
		wsa_log_last_error("WSA error listening on socket");
		throw std::runtime_error(fmt::format("WSA error listening on socket {}", socket_.socket()));
	}
	SPDLOG_INFO("Listening on socket {}", socket_.socket());
}

Win_socket Win_server_socket::accept()
{
	SPDLOG_DEBUG("Accepting connections on socket {}", socket_.socket());

	SOCKET s = ::accept(socket_.socket(), nullptr, nullptr);
	if (s == INVALID_SOCKET) {
		wsa_log_last_error(fmt::format("Accept socket failed on listen socket {}: ", s));
	}
	return Win_socket(s);
}

}// namespace acutis::net::windows
