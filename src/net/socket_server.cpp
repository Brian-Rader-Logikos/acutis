#include "net/socket_server.h"
#include "socket_server_impl.h"

#if defined(_WIN32)
#include "windows/socket_server_win.h"
#elif defined(__unix) || defined(__APPLE__)
#include "posix/socket_server_posix.h"
#endif

#include <spdlog/spdlog.h>

namespace acutis::net {
namespace {
	auto create_socket_server()
	{
#if defined(_WIN32)
		return std::make_unique<windows::Socket_server_win>();
#elif defined(__unix) || defined(__APPLE__)
		return std::make_unique<Socket_server_posix>();
#endif
	}
}// namespace

Socket_server::Socket_server() : impl_(create_socket_server())
{
	SPDLOG_TRACE("Constructed Socket_server");
}

Socket_server::~Socket_server() noexcept
{
	SPDLOG_TRACE("Destroyed Socket_server");
}

Socket_server::Socket_server(Socket_server&& other) noexcept : impl_(std::move(other.impl_))
{
	SPDLOG_TRACE("Move constructed Socket_server");
}

Socket_server& Socket_server::operator=(Socket_server&& other) noexcept {
	impl_ = std::move(other.impl_);
	SPDLOG_TRACE("Move assigned Socket_server");
	return *this;
}

void Socket_server::initialize()
{
	impl_->initialize();
}

void Socket_server::listen(Address address, uint16_t port)
{
	impl_->listen(address, port);
}

}// namespace acutis::net
