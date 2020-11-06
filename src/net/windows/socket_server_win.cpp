#include "socket_server_win.h"

#include "win_socket_api.h"

namespace acutis::net::windows {
namespace {
	internal::Win_socket_api s_wsa_api{};
}

void Socket_server_win::listen(Address /*address*/, int /*port*/)
{
	internal::Win_socket_api::initialize();
}

void Socket_server_win::cleanup() { internal::Win_socket_api::cleanup(); }

}// namespace acutis::net::windows
