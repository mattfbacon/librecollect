#include "Error.hpp"
#include "Memcache.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

uint64_t Memcache::increment(std::string_view const key, uint32_t const offset) {
	uint64_t ret;
	memcached_return_t const err = memcached_increment(m_handle, key.data(), key.size(), offset, &ret);
	if (memcached_failed(err)) {
		throw Error{ err };
	} else {
		return ret;
	}
}

uint64_t Memcache::increment(std::string_view const key, uint64_t const initial, uint32_t const offset, time_t const expiration) {
	uint64_t ret;
	memcached_return_t const err = memcached_increment_with_initial(m_handle, key.data(), key.size(), offset, initial, expiration, &ret);
	if (memcached_failed(err)) {
		throw Error{ err };
	} else {
		return ret;
	}
}

uint64_t Memcache::decrement(std::string_view const key, uint32_t const offset) {
	uint64_t ret;
	memcached_return_t const err = memcached_decrement(m_handle, key.data(), key.size(), offset, &ret);
	if (memcached_failed(err)) {
		throw Error{ err };
	} else {
		return ret;
	}
}

uint64_t Memcache::decrement(std::string_view const key, uint64_t const initial, uint32_t const offset, time_t const expiration) {
	uint64_t ret;
	memcached_return_t const err = memcached_decrement_with_initial(m_handle, key.data(), key.size(), offset, initial, expiration, &ret);
	if (memcached_failed(err)) {
		throw Error{ err };
	} else {
		return ret;
	}
}

}  // namespace LIB_RECOLLECT_NAMESPACE
