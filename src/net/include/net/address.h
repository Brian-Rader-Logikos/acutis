#ifndef ACUTIS_ADDRESS_H
#define ACUTIS_ADDRESS_H

#include <string_view>

namespace acutis::net {

class Address {
public:
	explicit Address(std::string_view address);
};

}// namespace acutis::net

#endif// !ACUTIS_ADDRESS_H
