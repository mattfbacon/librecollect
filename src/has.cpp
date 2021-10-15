#include "Error.hpp"
#include "Memcache.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

bool Memcache::has(std::string_view const key) const {
	memcached_return_t const err = memcached_exist(m_handle, key.data(), key.size());
	if (err == MEMCACHED_NOTFOUND) {
		return false;
	} else if (memcached_failed(err)) {
		throw Error{ err };
	} else {
		return true;
	}
}

}  // namespace LIB_RECOLLECT_NAMESPACE
