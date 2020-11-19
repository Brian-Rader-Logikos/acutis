#include "socket_server_posix.h"

#include <spdlog/spdlog.h>
#include <mutex>

namespace acutis::net {

Socket_server_posix::Socket_server_posix()
{
	SPDLOG_TRACE("Constructed Socket_server_posix");
}

Socket_server_posix::~Socket_server_posix()
{
	SPDLOG_TRACE("Destroyed Socket_server_posix");
}

Socket_server_posix::Socket_server_posix(Socket_server_posix&& other) noexcept
  : server_socket_(std::move(other.server_socket_))
{
	SPDLOG_TRACE("Destroyed Socket_server_posix");
}

Socket_server_posix& Socket_server_posix::operator=(Socket_server_posix&& other) noexcept
{
	server_socket_ = std::move(other.server_socket_);
	SPDLOG_TRACE("Move assigned Socket_server_posix");
	return *this;
}

void Socket_server_posix::initialize()
{
}

void Socket_server_posix::listen(Address address, uint16_t port)
{
	server_socket_ = create_posix_server_socket();
	server_socket_.bind(address, port);
	server_socket_.listen();
	Posix_socket new_socket = server_socket_.accept();

	SPDLOG_DEBUG("New client connection on socket {}", new_socket.socket());
	new_socket.close();
	server_socket_.close();
}

}// namespace acutis::net
