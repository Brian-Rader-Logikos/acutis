#ifndef ACUTIS_SOCKET_SERVER_H
#define ACUTIS_SOCKET_SERVER_H

#include "net/address.h"
#include <memory>

namespace acutis::net {

namespace internal {
	class Socket_server_impl;
}

class Socket_server {
public:
	Socket_server();
	~Socket_server() noexcept;

	Socket_server(const Socket_server&) = delete;
	Socket_server(Socket_server&& other) noexcept;

	Socket_server& operator=(const Socket_server&) = delete;
	Socket_server& operator=(Socket_server&& other) noexcept;

	void initialize();
	void listen(Address address, uint16_t port);

private:
	std::unique_ptr<internal::Socket_server_impl> impl_;
};

}// namespace acutis::net

#endif// !ACUTIS_SOCKET_SERVER_H
