#pragma once

#include <stdexcept>

class SocketException : public std::runtime_error {

	// use std::runtime_error functions
	public:
		explicit SocketException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) {}
        ~SocketException(void) = default;

	// copy - move operators
	public:
		const SocketException &operator=(const SocketException &) throw() = delete;

	// what
	public:
		const char *what(void) const throw() { return mWhat.c_str(); }

	// attributes
	private:
		std::string mWhat;

};
