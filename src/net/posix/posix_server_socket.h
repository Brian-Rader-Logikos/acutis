#ifndef ACUTIS_POSIX_SERVER_SOCKET_H
#define ACUTIS_POSIX_SERVER_SOCKET_H

#include "net/address.h"
#include "posix_socket.h"

namespace acutis::net {

class Posix_server_socket {
public:
	Posix_server_socket() = default;
	explicit Posix_server_socket(Posix_socket&& socket);
	~Posix_server_socket();

	Posix_server_socket(const Posix_server_socket&) = delete;
	Posix_server_socket(Posix_server_socket&& other) noexcept;

	Posix_server_socket& operator=(const Posix_server_socket&) = delete;
	Posix_server_socket& operator=(Posix_server_socket&& other) noexcept;

	void close();
	void bind(Address address, uint16_t port);
	void listen();
	Posix_socket accept();

	[[nodiscard]] int socket() const { return socket_.socket(); }
	[[nodiscard]] bool is_open() const { return socket_.is_open(); }

private:
	Posix_socket socket_;
};

Posix_server_socket create_posix_server_socket();

}// namespace acutis::net
#endif// !ACUTIS_POSIX_SERVER_SOCKET_H
