#pragma once

#include <stdexcept>

class MutexException : public std::runtime_error {

	// use std::runtime_error functions
	public:
		explicit MutexException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) {}
        ~MutexException(void) = default;

	// copy - move operators
	public:
		const MutexException &operator=(const MutexException &) throw() = delete;

	// what
	public:
		const char *what(void) const throw() { return mWhat.c_str(); }

	// attributes
	private:
		std::string mWhat;

};
