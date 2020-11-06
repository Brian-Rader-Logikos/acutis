#ifndef ACUTIS_SOCKET_SERVER_IMPL_H
#define ACUTIS_SOCKET_SERVER_IMPL_H

namespace acutis::net::internal {

class Socket_server_impl {
public:
	Socket_server_impl() = default;
	virtual ~Socket_server_impl(){};
	Socket_server_impl(const Socket_server_impl&) = delete;
	Socket_server_impl(Socket_server_impl&&) = delete;
	Socket_server_impl& operator=(const Socket_server_impl&) = delete;
	Socket_server_impl& operator=(Socket_server_impl&&) = delete;

	virtual void listen(Address address, int port) = 0;
	virtual void cleanup() = 0;
};

}// namespace acutis::net::internal

#endif// !ACUTIS_SOCKET_SERVER_IMPL_H
