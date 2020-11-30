#ifndef ACUTIS_DOUBLES_STUB_STREAM_H
#define ACUTIS_DOUBLES_STUB_STREAM_H

#include <string>

#include "stream/stream.h"

namespace acutis::test_doubles {

class Stub_stream : public acutis::stream::Stream {
public:
	explicit Stub_stream(std::string content);
	~Stub_stream() override {}

	void read_some(std::deque<char>& buffer) override;

private:
	std::string content_;
};

}// namespace acutis::test_doubles

#endif// !ACUTIS_DOUBLES_STUB_STREAM_H
