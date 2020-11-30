#ifndef ACUTIS_HTTP_MESSAGE_H
#define ACUTIS_HTTP_MESSAGE_H

#include "http/method.h"
#include "http/uri.h"
#include "http/version.h"

namespace acutis::http {

struct Message {
	bool is_request{ false };
	Method method{ Method::Unknown };
	Uri uri;
	Version http_version;
};
}// namespace acutis::http

#endif// !ACUTIS_HTTP_MESSAGE_H
