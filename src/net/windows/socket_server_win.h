#ifndef ACUTIS_WIN_SOCKET_SERVER_H
#define ACUTIS_WIN_SOCKET_SERVER_H

#include "net/address.h"
#include "socket_server_impl.h"

namespace acutis::net::windows {

class Socket_server_win : public acutis::net::internal::Socket_server_impl {
public:
	Socket_server_win() = default;
	void listen(Address address, int port) override;
	void cleanup() override;
};

}// namespace acutis::net::windows

#endif// !ACUTIS_WIN_SOCKET_SERVER_H
