#include "windows/win_util.h"
#include <string>
#include <windows.h>

namespace acutis::net::windows {

std::string error_message(int error)
{
	LPTSTR msg_buffer = nullptr;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPTSTR>(&msg_buffer), 0, nullptr);

	std::string message = msg_buffer;
	LocalFree(msg_buffer);
	return message;
}

}// namespace acutis::net::windows
