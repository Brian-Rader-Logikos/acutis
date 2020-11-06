#include "net/socket_server.h"
#include "socket_server_impl.h"

#include "windows/socket_server_win.h"

namespace acutis::net {

Socket_server::Socket_server()
{
	impl_ = std::make_unique<windows::Socket_server_win>();
}

Socket_server::~Socket_server()
{
	impl_->cleanup();
}

void Socket_server::listen(Address address, int port)
{
	impl_->listen(address, port);
}

void Socket_server::shutdown() {}

}// namespace acutis::net
