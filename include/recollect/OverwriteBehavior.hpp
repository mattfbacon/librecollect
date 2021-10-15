#pragma once

#include "common.hpp"
#include "fwd.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

enum class OverwriteBehavior : unsigned char {
	ignore,
	require,
	require_not,
};

};
