#include "Error.hpp"
#include "Memcache.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

void Memcache::set(std::string_view const key, std::string_view const value, OverwriteBehavior const overwrite_behavior, uint32_t const flags, time_t const expiration) {
	memcached_return_t const err = (setter_for_overwrite_behavior(overwrite_behavior))(m_handle, key.data(), key.size(), value.data(), value.size(), expiration, flags);
	if (memcached_failed(err)) {
		throw Error{ err };
	}
}

}  // namespace LIB_RECOLLECT_NAMESPACE
