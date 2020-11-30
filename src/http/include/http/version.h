#ifndef ACUTIS_HTTP_VERSION_H
#define ACUTIS_HTTP_VERSION_H

#include <cstdint>

namespace acutis::http {

struct Version {
	uint16_t major{ 0 };
	uint16_t minor{ 0 };
};
}// namespace acutis::http

#endif// !ACUTIS_HTTP_VERSION_H
