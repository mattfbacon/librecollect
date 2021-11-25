#pragma once

#include <libmemcached-1.0/memcached.h>
#include <type_traits>

#include "common.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

class ConnectionMeans;

enum class OverwriteBehavior : unsigned char;

class Memcache;
class Value;

struct Error;

}  // namespace LIB_RECOLLECT_NAMESPACE
