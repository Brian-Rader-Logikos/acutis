#ifndef ACUTIS_WIN_SOCKET_SERVER_H
#define ACUTIS_WIN_SOCKET_SERVER_H

#include "net/address.h"
#include "socket_server_impl.h"
#include "win_server_socket.h"

namespace acutis::net::windows {

class Socket_server_win : public acutis::net::internal::Socket_server_impl {
public:
	Socket_server_win();
	~Socket_server_win() override;

	Socket_server_win(const Socket_server_win&) = delete;
	Socket_server_win(Socket_server_win&& other) noexcept;

	Socket_server_win& operator=(const Socket_server_win&) = delete;
	Socket_server_win& operator=(Socket_server_win&& other) noexcept;

	void initialize() override;
	void listen(Address address, uint16_t port) override;

private:
	Win_server_socket server_socket_;
};

}// namespace acutis::net::windows

#endif// !ACUTIS_WIN_SOCKET_SERVER_H
