#include "Error.hpp"
#include "Memcache.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

void Memcache::flush_buffers() const {
	memcached_return_t const err = memcached_flush_buffers(m_handle);
	if (memcached_failed(err)) {
		throw Error{ err };
	}
}

}  // namespace LIB_RECOLLECT_NAMESPACE
