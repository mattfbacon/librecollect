#include <catch2/catch.hpp>

#include "instance.hpp"

TEST_CASE("flush") {
	// there isn't really a great way to test this
	CHECK_NOTHROW(memcache.flush_buffers());
}
