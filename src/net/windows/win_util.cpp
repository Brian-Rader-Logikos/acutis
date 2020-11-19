#include "windows/win_util.h"
#include <string>
#include <windows.h>
#include <spdlog/spdlog.h>

namespace acutis::net::windows {

namespace {
	std::string error_message(int error)
	{
		LPTSTR msg_buffer = nullptr;

		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM
						  | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<LPTSTR>(&msg_buffer), 0, nullptr);

		std::string message = msg_buffer;
		LocalFree(msg_buffer);
		return message;
	}
}// namespace

int wsa_log_last_error(std::string_view msg)
{
	const int error = WSAGetLastError();
	const std::string error_msg = error_message(error);
	SPDLOG_ERROR("{} {}: {}", msg, error, error_msg);
	return error;
}

}// namespace acutis::net::windows
