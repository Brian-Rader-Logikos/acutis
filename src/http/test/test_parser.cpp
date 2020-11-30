#include "http/parser.h"
#include "test_doubles/stub_stream.h"

#include <catch2/catch.hpp>
#include <string>
#include <ostream>

using namespace std::string_literals;
using namespace acutis::test_doubles;

using acutis::http::Method;
using acutis::http::Parse_error;
using acutis::http::Parser;
using acutis::http::Stream;

TEST_CASE("HTTP Requests", "[parser]")
{
	SECTION("Simple, single GET request")
	{
		Stub_stream stream{ "GET / HTTP/1.1\r\n\r\n"s };
		Stream& base_stream{ stream };
		Parser parser{ base_stream };

		auto [msg, err] = parser.read_request();

		REQUIRE(err == Parse_error::None);
		REQUIRE(msg.is_request);
		REQUIRE(msg.method == Method::GET);
		REQUIRE(msg.uri.to_string() == "/"s);
		REQUIRE(msg.http_version.major == 1);
		REQUIRE(msg.http_version.minor == 1);
	}

	SECTION("Two simple GET requests")
	{
		Stub_stream stream{ "GET req1 HTTP/1.1\r\n\r\nGET req2 HTTP/1.1\r\n\r\n"s };

		Stream& base_stream{ stream };
		Parser parser{ base_stream };

		auto [msg1, err1] = parser.read_request();
		auto [msg2, err2] = parser.read_request();

		REQUIRE(err1 == Parse_error::None);
		REQUIRE(msg1.uri.to_string() == "req1"s);

		REQUIRE(err2 == Parse_error::None);
		REQUIRE(msg2.uri.to_string() == "req2"s);
	}

	SECTION("GET method too short")
	{
		Stub_stream stream{ "GE / HTTP/1.1\r\n\r\n"s };
		Stream& base_stream{ stream };
		Parser parser{ base_stream };

		auto [msg, err] = parser.read_request();

		REQUIRE(err == Parse_error::bad_method);
		REQUIRE(msg.method == Method::Unknown);
	}

	SECTION("GET method too long")
	{
		Stub_stream stream{ "GETT / HTTP/1.1\r\n\r\n"s };
		Stream& base_stream{ stream };
		Parser parser{ base_stream };

		auto [msg, err] = parser.read_request();

		REQUIRE(err == Parse_error::bad_method);
		REQUIRE(msg.method == Method::Unknown);
	}
}

