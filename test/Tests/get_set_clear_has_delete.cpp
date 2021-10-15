#include <catch2/catch.hpp>

#include "instance.hpp"

TEST_CASE("get, set, clear, has, delete") {
	WHEN("the entire cache is cleared with `clear`") {
		memcache.clear();
		THEN("an arbitrary key should not have a value") {
			auto const value = memcache.get("abc");
			CHECK(!value.has_value());
		}
	}
	WHEN("a key with flags is set with `set`") {
		memcache.set("abc", "def", LIB_RECOLLECT_NAMESPACE::OverwriteBehavior::ignore, 1234U);
		THEN("the key with those flags should be returned by `get`") {
			auto const value = memcache.get("abc");
			CHECK(value.has_value());
			CHECK(value.sv() == "def");
			CHECK(value.flags == 1234U);
		}
	}
	WHEN("the key is deleted with `delete`") {
		memcache.delete_("abc");
		THEN("the key should not be contained (as reported by `has`)") {
			CHECK(!memcache.has("abc"));
		}
	}
}
