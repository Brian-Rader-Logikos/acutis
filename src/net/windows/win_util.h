#ifndef ACUTIS_WIN_UTIL_H
#define ACUTIS_WIN_UTIL_H

#include <string>

namespace acutis::net::windows {

int wsa_log_last_error(std::string_view msg);

}
#endif// !ACUTIS_WIN_UTIL_H
