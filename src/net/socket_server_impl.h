#ifndef ACUTIS_SOCKET_SERVER_IMPL_H
#define ACUTIS_SOCKET_SERVER_IMPL_H

#include "net/address.h"

namespace acutis::net::internal {

class Socket_server_impl {
public:
	Socket_server_impl() = default;
	virtual ~Socket_server_impl() = default;
	Socket_server_impl(const Socket_server_impl&) = delete;
	Socket_server_impl(Socket_server_impl&&) = delete;
	Socket_server_impl& operator=(const Socket_server_impl&) = delete;
	Socket_server_impl& operator=(Socket_server_impl&&) = delete;

	virtual void initialize() = 0;
	virtual void listen(Address address, uint16_t port) = 0;
};

}// namespace acutis::net::internal

#endif// !ACUTIS_SOCKET_SERVER_IMPL_H
