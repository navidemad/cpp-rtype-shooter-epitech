#pragma once

#include <stdexcept>

class CondVarException : public std::runtime_error {

	// use std::runtime_error functions
	public:
		explicit CondVarException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) {}
		~CondVarException(void) {}

	// copy - move operators
	public:
		const CondVarException &operator=(const CondVarException &) throw() = delete;

	// what
	public:
		const char *what(void) const throw() { return mWhat.c_str(); }

	// attributes
	private:
		std::string mWhat;

};
