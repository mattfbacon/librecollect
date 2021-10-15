#include <catch2/catch.hpp>

#include "instance.hpp"

TEST_CASE("behavior") {
	auto const saved_behavior = memcache.get_behavior(MEMCACHED_BEHAVIOR_HASH);
	WHEN("the behavior is set") {
		memcache.set_behavior(MEMCACHED_BEHAVIOR_HASH, MEMCACHED_HASH_JENKINS);
		THEN("the same value should be returned when getting it") {
			CHECK(memcache.get_behavior(MEMCACHED_BEHAVIOR_HASH) == MEMCACHED_HASH_JENKINS);
		}
	}
	memcache.set_behavior(MEMCACHED_BEHAVIOR_HASH, saved_behavior);
	CHECK(memcache.get_behavior(MEMCACHED_BEHAVIOR_HASH) == saved_behavior);
}
