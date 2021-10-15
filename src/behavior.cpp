#include "Error.hpp"
#include "Memcache.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

uint64_t Memcache::get_behavior(memcached_behavior_t const behavior) const {
	return memcached_behavior_get(m_handle, behavior);
}

void Memcache::set_behavior(memcached_behavior_t const behavior, uint64_t const data) const {
	memcached_return_t const err = memcached_behavior_set(m_handle, behavior, data);
	if (memcached_failed(err)) {
		throw Error{ err };
	}
}

}  // namespace LIB_RECOLLECT_NAMESPACE
