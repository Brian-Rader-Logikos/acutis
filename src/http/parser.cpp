#include "http/parser.h"

#include <algorithm>
#include <cctype>

namespace acutis::http {

Parser::Parser(Stream& stream) : stream_(stream) {}

Read_response Parser::read_request()
{
	Read_response result;

	stream_.read_some(buffer_);

	result.error = parse_request_line(result.message);
	buffer_.pop_front();// \r
	buffer_.pop_front();// \n

	return result;
}

constexpr bool is_not_space(char c)
{
	return c != ' ';
}

constexpr uint16_t to_version_digit(char c)
{
	return static_cast<uint16_t>(c - '0');
}

template<typename Iter>
auto find_next_token(Iter iter1, Iter iter2, const char delimeter)
{
	auto token = std::pair(iter1, std::find(iter1, iter2, delimeter));
	auto after_token = std::pair(std::next(token.second), iter2);
	return std::pair(token, after_token);
}

template<typename Iter>
auto find_next_token(std::pair<Iter, Iter> segment, const char delimeter)
{
	return find_next_token(segment.first, segment.second, delimeter);
}

template<typename Container>
auto find_next_line(const Container& c)
{
	auto [line, after_line] = find_next_token(std::cbegin(c), std::cend(c), '\r');
	std::advance(after_line.first, 1);// skip '\n'
	return std::pair(line, after_line);
}

template<typename Iter>
bool matches_string(std::pair<Iter, Iter> segment, const std::string& value)
{
	auto [diff1, diff2] = std::mismatch(std::cbegin(value), std::cend(value), segment.first);
	return (diff1 == std::cend(value) && diff2 == segment.second);
}

Parse_error Parser::parse_request_line(Message& message)
{
	Parse_error error{ Parse_error::Unknown };

	static const std::string get_method{ "GET" };

	auto [req_line, after_line] = find_next_line(buffer_);

	auto [method, after_method] = find_next_token(req_line, ' ');

	if (matches_string(method, get_method)) {
		message.method = Method::GET;
	}
	else {
		error = Parse_error::bad_method;
	}

	auto [uri_tok, version_tok] = find_next_token(after_method, ' ');
	std::string uri;
	std::copy(uri_tok.first, uri_tok.second, std::back_inserter(uri));
	message.uri = Uri::from_string(uri);

	auto minor_digit = std::prev(version_tok.second);
	auto major_digit = std::prev(minor_digit, 2);
	message.http_version.major = to_version_digit(*major_digit);
	message.http_version.minor = to_version_digit(*minor_digit);

	message.is_request = true;
	buffer_.erase(req_line.first, after_line.first);

	if (error == Parse_error::Unknown) {
		error = Parse_error::None;
	}
	return error;
}

std::ostream& operator<<(std::ostream& out, Parse_error error)
{
	return out << to_string(error);
}

}// namespace acutis::http
