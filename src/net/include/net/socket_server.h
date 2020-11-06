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
	~Socket_server();
	void listen(Address address, int port);
	void shutdown();

private:
	std::unique_ptr<internal::Socket_server_impl> impl_;
};

}// namespace acutis::net

#endif// !ACUTIS_SOCKET_SERVER_H
