#ifndef ACUTIS_WIN_SOCKET_API_H
#define ACUTIS_WIN_SOCKET_API_H

namespace acutis::net::windows::internal {

class Win_socket_api {
public:
	Win_socket_api(const Win_socket_api&) = delete;
	Win_socket_api(Win_socket_api&&) = delete;
	Win_socket_api& operator=(const Win_socket_api&) = delete;
	Win_socket_api& operator=(Win_socket_api&&) = delete;

	static void initialize();
	static void cleanup();

private:
	static void do_initialize();
};

}// namespace acutis::net::windows::internal

#endif// !ACUTIS_WIN_SOCKET_API_H
