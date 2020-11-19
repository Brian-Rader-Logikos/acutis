#include "posix_server_socket.h"

#include <fmt/core.h>
#include <spdlog/spdlog.h>
#include <netdb.h>
#include <netinet/in.h>
#include "posix_util.h"

namespace acutis::net {

Posix_server_socket::Posix_server_socket(Posix_socket&& socket) : socket_(std::move(socket))
{
	SPDLOG_TRACE("Constructed server socket from socket {}", socket_.socket());
}

Posix_server_socket::Posix_server_socket(Posix_server_socket&& other) noexcept
  : socket_(std::move(other.socket_))
{
	SPDLOG_TRACE("Moved constructed server socket {}", socket_.socket());
}

Posix_server_socket::~Posix_server_socket()
{
	close();
	SPDLOG_TRACE("Destroyed Socket_server");
}

Posix_server_socket& Posix_server_socket::operator=(Posix_server_socket&& other) noexcept
{
	socket_ = std::move(other.socket_);
	SPDLOG_TRACE("Moved assigned server socket {}", socket_);
	return *this;
}

void Posix_server_socket::close()
{
	socket_.close();
}

Posix_server_socket create_posix_server_socket()
{
	return Posix_server_socket( create_posix_socket() );
}

void Posix_server_socket::bind(Address address, uint16_t port)
{
    const int reuse_value{1};
    int opt_result = setsockopt(socket_.socket(), SOL_SOCKET, SO_REUSEADDR, &reuse_value, sizeof(int));
    if( opt_result == -1 )
    {
		posix_log_last_error("Failure setting socket Reuse Address option");
    }

	sockaddr_in sa;
    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(address.to_ulong());
	sa.sin_port = htons(port);

	int result = ::bind(socket_.socket(), reinterpret_cast<sockaddr*>(&sa), sizeof(sa));
	if (result == -1) {
		posix_log_last_error("Posix error binding socket");
		throw std::runtime_error(fmt::format("Posix error binding socket {}", socket_.socket()));
	}
	SPDLOG_INFO("Bound socket {} on {}:{}", socket_.socket(), address.to_string(), port);
}

void Posix_server_socket::listen()
{
	int result = ::listen(socket_.socket(), SOMAXCONN);
	if (result == -1) {
		posix_log_last_error("Posix error listening on socket");
		throw std::runtime_error(fmt::format("Posix error listening on socket {}", socket_.socket()));
	}
	SPDLOG_INFO("Listening on socket {}", socket_.socket());
}

Posix_socket Posix_server_socket::accept()
{
	SPDLOG_DEBUG("Accepting connections on socket {}", socket_.socket());

	int s = ::accept(socket_.socket(), nullptr, nullptr);
	if (s == INVALID_SOCKET) {
		posix_log_last_error(fmt::format("Accept socket failed on listen socket {}: ", s));
	}
	return Posix_socket(s);
}

}// namespace acutis::net
