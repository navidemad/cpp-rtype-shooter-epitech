#include "SocketException.hpp"

SocketException::SocketException(const std::string &error)
	: std::runtime_error(error), mWhat(error) {}

const char	*SocketException::what(void) const throw() {
	return mWhat.c_str();
}
