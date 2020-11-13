#ifndef ACUTIS_WIN_SOCKET_H
#define ACUTIS_WIN_SOCKET_H

#include "net/address.h"

#include <winsock2.h>

namespace acutis::net::windows {

class Win_socket {
public:
	Win_socket();
	explicit Win_socket(SOCKET socket) noexcept;
	~Win_socket();

	Win_socket(const Win_socket&) = delete;
	Win_socket(Win_socket&& other) noexcept;

	Win_socket& operator=(const Win_socket&) = delete;
	Win_socket& operator=(Win_socket&& other) noexcept;

	void shutdown();
	void close();

	[[nodiscard]] SOCKET socket() const { return socket_; }
	[[nodiscard]] bool is_open() const { return socket_ != INVALID_SOCKET; }

private:
	SOCKET socket_ = INVALID_SOCKET;
};

Win_socket create_win_socket();

}// namespace acutis::net::windows

#endif// !ACUTIS_WIN_SOCKET_H
