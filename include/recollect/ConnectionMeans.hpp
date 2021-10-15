#pragma once

#include <string>

#include "common.hpp"
#include "fwd.hpp"

namespace LIB_RECOLLECT_NAMESPACE {

class ConnectionMeans {
protected:
	static constexpr int DEFAULT_PORT = 11211;
	static constexpr int INVALID_PORT = -1;
protected:
	std::string m_name;
	int m_port;
	ConnectionMeans(std::string name, int port) : m_name(std::move(name)), m_port(std::move(port)) {}
public:
	void add_to_conn(Memcache& conn) const;
public:
	static ConnectionMeans tcp(std::string url = "localhost", int const port = DEFAULT_PORT) {
		return ConnectionMeans{ std::move(url), port };
	}
	static ConnectionMeans unix_socket(std::string path) {
		return ConnectionMeans{ std::move(path), INVALID_PORT };
	}
};

}  // namespace LIB_RECOLLECT_NAMESPACE
