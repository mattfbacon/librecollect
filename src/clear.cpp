#include "Memcache.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

void Memcache::clear(time_t const expiration) {
	memcached_flush(m_handle, expiration);
}

}  // namespace LIB_RECOLLECT_NAMESPACE
