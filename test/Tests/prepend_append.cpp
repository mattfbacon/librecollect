#include <catch2/catch.hpp>

#include "instance.hpp"

TEST_CASE("prepend, append") {
	GIVEN("a cache with one key") {
		memcache.clear();
		memcache.set("abc", "car", LIB_RECOLLECT_NAMESPACE::OverwriteBehavior::ignore, 1234U);
		{
			auto const value = memcache.get("abc");
			CHECK(value.has_value());
			CHECK(value.sv() == "car");
		}
		WHEN("something is prepended (with flags) to that key with `prepend`") {
			memcache.prepend("abc", "two ", 5678U);
			THEN("the content should have been prepended, but the flags should remain unchanged") {
				auto const value = memcache.get("abc");
				CHECK(value.has_value());
				CHECK(value.sv() == "two car");
				CHECK(value.flags == 1234U);
			}
		}
		WHEN("something is appended (with other flags) to that key with `append`") {
			memcache.append("abc", " garage", 9012U);
			THEN("the content should have been appended, but the flags should remain unchanged") {
				auto const value = memcache.get("abc");
				CHECK(value.has_value());
				// could be "car garage" if the previous request hasn't settled
				CHECK((value.sv() == "two car garage" || value.sv() == "car garage"));
				CHECK(value.flags == 1234U);
			}
		}
	}
}
