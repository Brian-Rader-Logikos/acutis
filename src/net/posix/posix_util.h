#ifndef ACUTIS_POSIX_UTIL_H
#define ACUTIS_POSIX_UTIL_H

#include <string>

namespace acutis::net {

int posix_log_last_error(std::string_view msg);

}
#endif// !ACUTIS_POSIX_UTIL_H
