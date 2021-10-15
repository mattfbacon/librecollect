#pragma once

#include <libmemcached-1.0/memcached.h>
#include <stdexcept>

#include "common.hpp"
#include "fwd.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

struct Error : public std::exception {
	memcached_return_t err_code;
	Error(memcached_return_t err_code) : std::exception{}, err_code(err_code) {}
	char const* what() const noexcept override {
		// the memcached_st pointer is not used by the strerror function
		return memcached_strerror(nullptr, err_code);
	}
};

}  // namespace LIB_RECOLLECT_NAMESPACE
