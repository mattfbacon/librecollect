#include <catch2/catch.hpp>

#include "instance.hpp"

TEST_CASE("_handle") {
	WHEN("the handle is fetched") {
		auto* const handle = memcache._handle();
		THEN("it should not be null") {
			CHECK(handle != nullptr);
		}
	}
}
