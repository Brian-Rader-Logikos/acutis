#ifndef ACUTIS_STREAM_H
#define ACUTIS_STREAM_H

#include <deque>

namespace acutis::stream {

class Stream {
public:
	Stream() = default;
	virtual ~Stream() = default;
	Stream(const Stream&) = delete;
	Stream(Stream&&) = delete;
	Stream& operator=(const Stream&) = delete;
	Stream& operator=(Stream&&) = delete;

	virtual void read_some(std::deque<char>& buffer) = 0;
};

}// namespace acutis::stream
#endif// !ACUTIS_STREAM_H
