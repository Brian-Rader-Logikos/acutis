#include "http/uri.h"

namespace acutis::http {

Uri Uri::from_string(std::string_view uri)
{
	Uri new_uri;
	new_uri.uri_ = uri;
	return new_uri;
}

}// namespace acutis::http
