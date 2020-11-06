#include "socket_server_win.h"

#include "win_socket_api.h"

namespace acutis::net::windows {

Socket_server_win::~Socket_server_win() {
	internal::wsa_cleanup();
}

void Socket_server_win::listen(Address /*address*/, int /*port*/)
{
	internal::wsa_initialize();
}

void Socket_server_win::cleanup()
{
	internal::wsa_cleanup();
}

}// namespace acutis::net::windows
