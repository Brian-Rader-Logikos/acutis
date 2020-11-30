#ifndef ACUTIS_HTTP_METHOD_H
#define ACUTIS_HTTP_METHOD_H

#include <ostream>
#include <string_view>

namespace acutis::http {

enum class Method { Unknown, GET };

constexpr std::string_view to_string(Method method)
{
	switch (method) {
	 case Method::Unknown:
		return "Unknown";
	case Method::GET:
		return "GET";
	}
	return "Unknown";
}

std::ostream& operator<<(std::ostream& out, Method method);

}// namespace acutis::http
#endif// !ACUTIS_HTTP_METHOD_H
