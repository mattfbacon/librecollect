#pragma once

#include <memory>

#include "common.hpp"
#include "fwd.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

struct FreeDeleter {
	void operator()(void* ptr) const {
		free(ptr);
	}
};

class Value {
protected:
	std::unique_ptr<char, FreeDeleter> ptr;
	size_t size = 0;
	uint32_t flags = 0;
	explicit Value() : ptr{ nullptr, FreeDeleter{} } {}
	explicit Value(char* ptr, size_t size, uint32_t flags) : ptr{ ptr, FreeDeleter{} }, size{ size }, flags{ flags } {}
public:
	std::string_view sv() const {
		return std::string_view{ ptr.get(), size };
	}
	bool has_value() const {
		return ptr.get() != nullptr;
	}
	operator char*() {
		return ptr.get();
	}
	operator char const *() const {
		return ptr.get();
	}
	bool operator==(Value const& other) {
		if (!has_value() && !other.has_value()) {
			return true;
		}
		return sv() == other.sv();
	}
	bool operator==(std::string_view const& other) {
		if (!has_value() && other.data() == nullptr) {
			return true;
		}
		return sv() == other;
	}
};

}  // namespace LIB_RECOLLECT_NAMESPACE
