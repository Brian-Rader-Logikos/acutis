#ifndef ACUTIS_ADDRESS_H
#define ACUTIS_ADDRESS_H

#include <array>
#include <string_view>

namespace acutis::net {

class Address {
public:
	Address() = default;
	explicit Address(std::array<uint8_t, 4> bytes);

	uint32_t to_ulong();
	std::string to_string();

private:
	std::array<uint8_t, 4> bytes_ = { 0, 0, 0, 0 };
};

Address address_from_string(std::string_view addr_str);

}// namespace acutis::net

#endif// !ACUTIS_ADDRESS_H
