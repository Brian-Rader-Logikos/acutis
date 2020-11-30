#ifndef ACUTIS_HTTP_PARSER_H
#define ACUTIS_HTTP_PARSER_H

#include "http/message.h"
#include "stream/stream.h"

#include <deque>
#include <ostream>
#include <string_view>

namespace acutis::http {
using acutis::stream::Stream;

enum class Parse_error { None, Unknown, bad_method };

struct Read_response {
	Message message;
	Parse_error error{ Parse_error::Unknown };
};

class Parser {
public:
	explicit Parser(Stream& stream);

	Read_response read_request();

private:
	Parse_error parse_request_line(Message& message);

	Stream& stream_;
	std::deque<char> buffer_;
};

constexpr std::string_view to_string(Parse_error error)
{
	switch (error) {
	case Parse_error::None:
		return "None";
	case Parse_error::Unknown:
		return "Unknown";
	case Parse_error::bad_method:
		return "Bad Method";
	}
	return "Unknown";
}

std::ostream& operator<<(std::ostream& out, Parse_error error);

}// namespace acutis::http
#endif// !ACUTIS_HTTP_PARSER_H
