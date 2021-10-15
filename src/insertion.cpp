#include "Error.hpp"
#include "Memcache.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

void Memcache::prepend(std::string_view const key, std::string_view const prefix, uint32_t const flags, time_t const expiration) {
	memcached_return_t const err = memcached_prepend(m_handle, key.data(), key.size(), prefix.data(), prefix.size(), expiration, flags);
	if (memcached_failed(err)) {
		throw Error{ err };
	}
}

void Memcache::append(std::string_view const key, std::string_view const prefix, uint32_t const flags, time_t const expiration) {
	memcached_return_t const err = memcached_append(m_handle, key.data(), key.size(), prefix.data(), prefix.size(), expiration, flags);
	if (memcached_failed(err)) {
		throw Error{ err };
	}
}

}  // namespace LIB_RECOLLECT_NAMESPACE
