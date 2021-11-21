#pragma once

#include <libmemcached-1.0/memcached.h>
#include <string>

#include "ConnectionMeans.hpp"
#include "OverwriteBehavior.hpp"
#include "Value.hpp"

#include "common.hpp"
#include "fwd.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

class Memcache {
public:
	explicit Memcache();
	template <typename Container>
	Memcache(Container connection_means) : Memcache() {
		for (auto const& mean : connection_means) {
			mean.add_to_conn(*this);
		}
	}
	Memcache(std::initializer_list<ConnectionMeans> connection_means) {
		for (auto const& mean : connection_means) {
			mean.add_to_conn(*this);
		}
	}
	Memcache(Memcache const& other);
	~Memcache();

	memcached_st* _handle() const {
		return m_handle;
	}

	Value get(std::string_view key) const;
	void set(std::string_view key, std::string_view value, OverwriteBehavior overwrite_behavior = OverwriteBehavior::ignore, uint32_t flags = 0, time_t expiration = 0);

	void prepend(std::string_view key, std::string_view prefix, uint32_t flags = 0, time_t expiration = 0);
	void append(std::string_view key, std::string_view suffix, uint32_t flags = 0, time_t expiration = 0);

	bool delete_(std::string_view key, time_t expiration = 0);
	bool has(std::string_view key) const;

	void clear(time_t expiration = 0);

	uint64_t increment(std::string_view key, uint32_t offset);
	uint64_t decrement(std::string_view key, uint32_t offset);
	uint64_t increment(std::string_view key, uint64_t initial, uint32_t offset, time_t expiration = 0);
	uint64_t decrement(std::string_view key, uint64_t initial, uint32_t offset, time_t expiration = 0);

	uint64_t get_behavior(memcached_behavior_t behavior) const;
	void set_behavior(memcached_behavior_t behavior, uint64_t data) const;

	void flush_buffers() const;
protected:
	static decltype(memcached_set)* setter_for_overwrite_behavior(OverwriteBehavior overwrite_behavior) {
		switch (overwrite_behavior) {
			case OverwriteBehavior::ignore:
				return memcached_set;
			case OverwriteBehavior::require:
				return memcached_replace;
			case OverwriteBehavior::require_not:
				return memcached_add;
			default:
				__builtin_unreachable();
		}
	}
protected:
	memcached_st* m_handle;
};

}  // namespace LIB_RECOLLECT_NAMESPACE
