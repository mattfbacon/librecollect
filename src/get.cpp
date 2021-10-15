#include "Error.hpp"
#include "Memcache.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

Value Memcache::get(std::string_view const key) const {
	Value ret;
	memcached_return_t err;
	ret.ptr.reset(memcached_get(m_handle, key.data(), key.size(), &ret.size, &ret.flags, &err));
	if (memcached_failed(err) && err != MEMCACHED_NOTFOUND) {
		throw Error{ err };
	} else {
		return ret;
	}
}

}  // namespace LIB_RECOLLECT_NAMESPACE
