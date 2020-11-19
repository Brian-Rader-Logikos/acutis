#include "posix/posix_util.h"
#include <string>
#include <spdlog/spdlog.h>
#include <errno.h>
#include <array>
#include <string.h>

namespace acutis::net {

namespace {
	std::string error_message(int error)
	{
        char buffer[256];
        // std::array<char, 256> buffer;
        [[maybe_unused]] auto r = strerror_r(error, &buffer[0], 256);
		return std::string(&buffer[0]);
	}
}// namespace

int posix_log_last_error(std::string_view msg)
{
	const int error = EISCONN; //errno;
	const std::string error_msg = error_message(errno);
	SPDLOG_ERROR("{} Error={}: {}", msg, error, error_msg);
	return error;
}

}// namespace acutis::net::windows
