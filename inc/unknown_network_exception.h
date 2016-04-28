#ifndef UNKNOWN_NETWORK_EXCEPTION_H
#define UNKNOWN_NETWORK_EXCEPTION_H

#include <stdexcept>
#include <string>

class UnknownNetworkException: public std::runtime_error {
	public:
		UnknownNetworkException(const std::string& msg): std::runtime_error(msg) {}
};

#endif
