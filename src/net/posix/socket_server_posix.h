#ifndef ACUTIS_SOCKET_SERVER_POSIX_H
#define ACUTIS_SOCKET_SERVER_POSIX_H

#include "net/address.h"
#include "socket_server_impl.h"
#include "posix_server_socket.h"

namespace acutis::net {

class Socket_server_posix : public acutis::net::internal::Socket_server_impl {
public:
	Socket_server_posix();
	~Socket_server_posix() override;

	Socket_server_posix(const Socket_server_posix&) = delete;
	Socket_server_posix(Socket_server_posix&& other) noexcept;

	Socket_server_posix& operator=(const Socket_server_posix&) = delete;
	Socket_server_posix& operator=(Socket_server_posix&& other) noexcept;

	void initialize() override;
	void listen(Address address, uint16_t port) override;

private:
	Posix_server_socket server_socket_;
};

}// namespace acutis::net

#endif// !ACUTIS_SOCKET_SERVER_POSIX_H
