#include "test_doubles/stub_stream.h"

namespace acutis::test_doubles {

Stub_stream::Stub_stream(std::string content) : content_{ std::move(content) } {}

void Stub_stream::read_some(std::deque<char>& buffer) {
	buffer.insert(std::end(buffer), std::begin(content_), std::end(content_));
	content_.clear();
}

}// namespace acutis::test_doubles
