#pragma once

#include <stdexcept>

class CommandException : public std::runtime_error {

	// use std::runtime_error functions
	public:
		explicit CommandException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) { }
        ~CommandException(void) = default;

	// copy - move operators
	public:
		const CommandException &operator=(const CommandException &) throw() = delete;

	// what
	public:
		const char *what(void) const throw() { return mWhat.c_str(); }

	// attributes
	private:
		const std::string& mWhat;

};
