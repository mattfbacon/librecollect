#include "ConnectionMeans.hpp"
#include "Memcache.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

Memcache::Memcache() {
	m_handle = memcached_create(nullptr);
	if (m_handle == nullptr) {
		throw std::bad_alloc{};
	}
}

Memcache::~Memcache() {
	memcached_free(m_handle);
	m_handle = nullptr;
}

Memcache::Memcache(Memcache const& other) {
	m_handle = memcached_clone(other.m_handle, nullptr);
	if (m_handle == nullptr) {
		throw std::bad_alloc{};
	}
}

}  // namespace LIB_RECOLLECT_NAMESPACE
