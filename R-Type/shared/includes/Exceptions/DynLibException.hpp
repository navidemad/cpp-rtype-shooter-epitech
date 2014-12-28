#pragma once

#include <stdexcept>

class DynLibException : public std::runtime_error {

	// use std::runtime_error functions
	public:
        DynLibException(const std::string & error) throw() : std::runtime_error(error), mWhat(error)  { }
        ~DynLibException(void) = default;

	// copy - move operators
	public:
		const DynLibException &operator=(const DynLibException &) throw() = delete;

	// what
	public:
		const char *what(void) const throw() { return mWhat.c_str(); }

	// attributes
	private:
		std::string mWhat;

};
