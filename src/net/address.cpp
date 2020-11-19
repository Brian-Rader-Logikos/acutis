#include "net/address.h"
#include <string_view>
#include <numeric>
#include <charconv>
#include <stdexcept>
#include <vector>
#include <fmt/core.h>
#include <algorithm>
#include <spdlog/spdlog.h>
#include <iterator>
#include <string>
#include <limits>

namespace acutis::net {
namespace {
	constexpr int bits_per_byte{ 8 };
	Address parse_ip_address(std::string_view addr_str);
}// namespace

Address::Address(std::array<uint8_t, 4> bytes) : bytes_(bytes) {}

uint32_t Address::to_ulong()
{
	return std::accumulate(cbegin(bytes_), cend(bytes_), static_cast<uint32_t>(0),
		[](uint32_t addr, uint8_t byte) { return (addr << bits_per_byte) | byte; });
}

std::string Address::to_string()
{
	return fmt::format("{}", fmt::join(bytes_, "."));
}


Address address_from_string(std::string_view addr_str)
{
	try {
		return parse_ip_address(addr_str);
	}
	catch (const std::exception& ex) {
		throw std::runtime_error(
			fmt::format("Could not convert '{}' to IP address. {}", addr_str, ex.what()));
	}
}

namespace {

	auto parse_first_segment(std::string_view source, std::string_view delimiters)
	{
		auto pos = source.find_first_of(delimiters);
		auto remaining =
			(pos == std::string_view::npos) ? std::string_view() : source.substr(pos + 1);
		return std::pair{ source.substr(0, pos), remaining };
	}

	uint8_t byte_from_segment(std::string_view segment)
	{
		int value = std::stoi(std::string(segment));

		if (value < std::numeric_limits<uint8_t>::lowest()
			|| value > std::numeric_limits<uint8_t>::max()) {
			throw std::runtime_error(fmt::format("Expected IP Address segment value from 0-255."));
		}
		return static_cast<uint8_t>(value);
	}

	Address parse_ip_address(std::string_view addr_str)
	{
		auto remaining = addr_str;
		std::array<uint8_t, 4> addr_bytes{ 0 };

		auto byte_pos = begin(addr_bytes);
		while (!remaining.empty() && byte_pos != end(addr_bytes)) {
			auto [segment, left] = parse_first_segment(remaining, ".");
			*byte_pos = byte_from_segment(segment);
			remaining = left;
			std::advance(byte_pos, 1);
		}

		if (byte_pos != end(addr_bytes) || !remaining.empty()) {
			throw std::runtime_error(fmt::format("Expected 4 IP Address segments."));
		}

		return Address(addr_bytes);
	}
}// namespace


}// namespace acutis::net
