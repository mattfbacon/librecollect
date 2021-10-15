#define CATCH_CONFIG_MAIN
// why not
#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>

#include "recollect/ConnectionMeans.hpp"
#include "recollect/Memcache.hpp"

LIB_RECOLLECT_NAMESPACE::Memcache memcache{
	LIB_RECOLLECT_NAMESPACE::ConnectionMeans::tcp("localhost", 11211),
	LIB_RECOLLECT_NAMESPACE::ConnectionMeans::unix_socket("/run/memcached/memcache.sock"),
};
