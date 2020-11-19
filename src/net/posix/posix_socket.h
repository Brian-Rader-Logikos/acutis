#ifndef ACUTIS_POSIX_SOCKET_H
#define ACUTIS_POSIX_SOCKET_H

#include "net/address.h"

namespace acutis::net {
static const int INVALID_SOCKET{-1};

class Posix_socket {
public:
	Posix_socket();
	explicit Posix_socket(int socket) noexcept;
	~Posix_socket();

	Posix_socket(const Posix_socket&) = delete;
	Posix_socket(Posix_socket&& other) noexcept;

	Posix_socket& operator=(const Posix_socket&) = delete;
	Posix_socket& operator=(Posix_socket&& other) noexcept;

	void shutdown();
	void close();

	[[nodiscard]] int socket() const { return socket_; }
	[[nodiscard]] bool is_open() const { return socket_ != INVALID_SOCKET; }

private:
	int socket_ = INVALID_SOCKET;
};

Posix_socket create_posix_socket();

}// namespace acutis::net

#endif// !ACUTIS_POSIX_SOCKET_H
