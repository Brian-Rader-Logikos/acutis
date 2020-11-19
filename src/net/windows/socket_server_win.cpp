#include "socket_server_win.h"

#include <spdlog/spdlog.h>
#include <winsock2.h>
#include <mutex>
#include "win_util.h"

namespace acutis::net::windows {
namespace {
	constexpr BYTE wsa_major = 2;
	constexpr BYTE wsa_minor = 0;
	constexpr WORD wsa_req_version = MAKEWORD(wsa_major, wsa_minor);
	std::once_flag wsa_init_flag;
	std::once_flag wsa_cleanup_flag;
	void wsa_cleanup();
}// namespace

Socket_server_win::Socket_server_win()
{
	SPDLOG_TRACE("Constructed Socket_server_win");
}

Socket_server_win::~Socket_server_win()
{
	wsa_cleanup();
	SPDLOG_TRACE("Destroyed Socket_server_win");
}

Socket_server_win::Socket_server_win(Socket_server_win&& other) noexcept
  : server_socket_(std::move(other.server_socket_))
{
	SPDLOG_TRACE("Destroyed Socket_server_win");
}

Socket_server_win& Socket_server_win::operator=(Socket_server_win&& other) noexcept
{
	server_socket_ = std::move(other.server_socket_);
	SPDLOG_TRACE("Move assigned Socket_server_win");
	return *this;
}

void Socket_server_win::initialize()
{
	std::call_once(wsa_init_flag, []() {
		WSADATA wsa_data;
		int result = WSAStartup(wsa_req_version, &wsa_data);
		if (result != 0) {
			wsa_log_last_error("WSA Startup error");
			throw std::runtime_error(
				fmt::format("Failure to initialize Windows Sockets v{}.{}", wsa_major, wsa_minor));
		}

		SPDLOG_DEBUG(
			"Initialized WSA v{}.{}", HIBYTE(wsa_data.wHighVersion), LOBYTE(wsa_data.wHighVersion));
	});
}

void Socket_server_win::listen(Address address, uint16_t port)
{
	server_socket_ = create_win_server_socket();
	server_socket_.bind(address, port);
	server_socket_.listen();
	Win_socket new_socket = server_socket_.accept();

	SPDLOG_DEBUG("New client connection on socket {}", new_socket.socket());
	new_socket.close();
	server_socket_.close();
}

namespace {

	void wsa_cleanup()
	{
		std::call_once(wsa_cleanup_flag, []() {
			int result = WSACleanup();
			if (result == 0) {
				SPDLOG_DEBUG("WSA Cleanup successful");
			}
			else {
				wsa_log_last_error("WSA Cleanup error");
			}
		});
	}

}// namespace

}// namespace acutis::net::windows
