#ifndef ACUTIS_HTTP_URI_H
#define ACUTIS_HTTP_URI_H

#include <string>
#include <string_view>

namespace acutis::http {

class Uri {
public:
	static Uri from_string(std::string_view uri);
	std::string to_string() const { return uri_; }

	private:
	std::string uri_;
};

}// namespace acutis::http
#endif// !ACUTIS_HTTP_URI_H
