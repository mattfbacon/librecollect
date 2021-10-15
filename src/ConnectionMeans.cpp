#include "ConnectionMeans.hpp"
#include "Memcache.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

void ConnectionMeans::add_to_conn(Memcache& conn) const {
	if (m_port == INVALID_PORT) {
		memcached_server_add_unix_socket(conn._handle(), m_name.c_str());
	} else {
		memcached_server_add(conn._handle(), m_name.c_str(), m_port);
	}
}

}  // namespace LIB_RECOLLECT_NAMESPACE
