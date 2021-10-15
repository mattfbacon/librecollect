#include "Error.hpp"
#include "Memcache.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

void Memcache::delete_(std::string_view const key, time_t const expiration) {
	memcached_return_t const err = memcached_delete(m_handle, key.data(), key.size(), expiration);
	if (memcached_failed(err)) {
		throw Error{ err };
	}
}

}  // namespace LIB_RECOLLECT_NAMESPACE
