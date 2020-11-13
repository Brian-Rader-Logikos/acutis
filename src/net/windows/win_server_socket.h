#ifndef ACUTIS_WIN_SERVER_SOCKET_H
#define ACUTIS_WIN_SERVER_SOCKET_H

#include "net/address.h"
#include "win_socket.h"

namespace acutis::net::windows {

class Win_server_socket {
public:
	Win_server_socket() = default;
	explicit Win_server_socket(Win_socket&& socket);
	~Win_server_socket();

	Win_server_socket(const Win_server_socket&) = delete;
	Win_server_socket(Win_server_socket&& other) noexcept;

	Win_server_socket& operator=(const Win_server_socket&) = delete;
	Win_server_socket& operator=(Win_server_socket&& other) noexcept;

	void close();
	void bind(Address address, uint16_t port);
	void listen();
	Win_socket accept();

	SOCKET socket() const { return socket_.socket(); }
	bool is_open() const { return socket_.is_open(); }

private:
	Win_socket socket_;
};

Win_server_socket create_win_server_socket();

}// namespace acutis::net::windows
#endif// !ACUTIS_WIN_SERVER_SOCKET_H
