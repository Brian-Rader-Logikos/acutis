#include <catch2/catch.hpp>

#include <array>
#include <list>
#include "net/address.h"
#include <string>

TEST_CASE("IPv4 addresses ", "[network]")
{
	using namespace acutis::net;
	using namespace std::literals::string_literals;

	SECTION("Default address")
	{
		Address address;

		REQUIRE(address.to_ulong() == 0x000000000000UL);
	}

	SECTION("Construct from byte array")
	{
		const std::array<uint8_t, 4> addr_bytes = { 0x12, 0x34, 0x56, 0x78 };

		Address address(addr_bytes);

		REQUIRE(address.to_ulong() == 0x12345678UL);
	}

	SECTION("Convert from string")
	{
		Address address = address_from_string("125.24.63.255");

		REQUIRE(address.to_ulong() == 0x7d183fffUL);
	}

	SECTION("Exception on invalid addresses")
	{
		using Catch::Matchers::Contains;
		const auto& addr_str = GENERATE(""s, "236"s, "1.2.3.4.5"s, "2..3.4"s, "5.a.6.7"s, "...."s,
			"255,255,255,255"s, "256.1.2.3"s, "1.256.2.3"s, "1.2.256.3"s, "1.2.3.256"s, "-1.1.2.3"s,
			"1.-1.2.3"s, "1.2.-1.3"s, "1.2.3.-1"s);
		INFO("Test Address " << addr_str);
		REQUIRE_THROWS_WITH(address_from_string(addr_str), Contains("Could not convert"));
	}

	SECTION("Address Boundaries")
	{
		using in_out = std::pair<std::string, uint32_t>;

		const auto& [addr_str, expected] = GENERATE(
			in_out{ "0.0.0.0"s, 0x00000000UL }, in_out{ "255.255.255.255"s, 0xffffffffUL });

		INFO("Test Address " << addr_str);

		Address address = address_from_string(addr_str);

		REQUIRE(address.to_ulong() == expected);
	}

	SECTION("Address to string") {
		using in_out = std::pair<std::array<uint8_t, 4>, std::string>;

		const auto& [addr_bytes, expected] = GENERATE(
			in_out{{ 0, 0, 0, 0 }, "0.0.0.0"s}, in_out{{255, 255, 255, 255}, "255.255.255.255"s});

		Address address{ addr_bytes };

		std::string addr_str = address.to_string();

		REQUIRE(addr_str == expected);
	}

}
