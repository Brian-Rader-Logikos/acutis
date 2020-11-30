#include "http/method.h"

namespace acutis::http {

std::ostream& operator<<(std::ostream& out, Method method)
{
	return out << to_string(method);
}

}// namespace acutis::http
