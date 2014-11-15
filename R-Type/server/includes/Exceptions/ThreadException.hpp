#pragma once

#include <stdexcept>

class ThreadException : public std::runtime_error {

	// use std::runtime_error functions
	public:
		ThreadException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) {}
		~ThreadException(void) {}

	// copy - move operators
	public:
		const ThreadException &operator=(const ThreadException &) throw() = delete;

	// what
	public:
		const char *what(void) const throw() { return mWhat.c_str(); }

	// attributes
	private:
        const std::string& mWhat;

};
