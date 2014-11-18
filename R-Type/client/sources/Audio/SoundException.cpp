#include "SoundException.hpp"

SoundException::SoundException(const std::string &error)
: std::runtime_error(error), mWhat(error) {}

const char	*SoundException::what(void) const throw() {
	return mWhat.c_str();
}
