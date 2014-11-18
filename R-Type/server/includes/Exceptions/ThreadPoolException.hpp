#pragma once

#include <stdexcept>

class ThreadPoolException : public std::runtime_error {

	// use std::runtime_error functions
	public:
		ThreadPoolException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) {}
		~ThreadPoolException(void) {}

	// copy - move operators
	public:
		const ThreadPoolException &operator=(const ThreadPoolException &) throw() = delete;

	// what
	public:
		const char *what(void) const throw() { return mWhat.c_str(); }

	// attributes
	private:
		const std::string& mWhat;

};
