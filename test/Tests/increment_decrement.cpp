#include <catch2/catch.hpp>

#include "instance.hpp"
#include "recollect/Error.hpp"

TEST_CASE("increment, decrement") {
	GIVEN("a cache with a numeric key") {
		memcache.clear();
		memcache.set("foo", "5");
		WHEN("that key is incremented") {
			auto value = memcache.increment("foo", 10);
			THEN("the resulting value should be correct") {
				CHECK(value == 15);
			}
		}
		WHEN("that key is decremented") {
			auto value = memcache.decrement("foo", 3);
			THEN("the resulting value should be correct") {
				// could be 2 if the previous request hasn't yet settled
				CHECK((value == 12 || value == 2));
			}
		}
		// not testing initial values because the availability depends on which protocol is being used
	}
	GIVEN("a cache with a non-numeric key") {
		memcache.clear();
		memcache.set("foo", "nonnumeric");
		WHEN("the key is incremented") {
			THEN("it should throw an error") {
				CHECK_THROWS_MATCHES(memcache.increment("foo", 10), LIB_RECOLLECT_NAMESPACE::Error, Catch::Matchers::Message("CLIENT ERROR"));
			}
		}
		WHEN("the key is decremented") {
			THEN("it should throw an error") {
				CHECK_THROWS_MATCHES(memcache.decrement("foo", 3), LIB_RECOLLECT_NAMESPACE::Error, Catch::Matchers::Message("CLIENT ERROR"));
			}
		}
	}
}
