#pragma once

#include <stdexcept>

class ScriptException : public std::runtime_error {

	// use std::runtime_error functions
	public:
		ScriptException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) {}
        ~ScriptException(void) = default;

	// copy - move operators
	public:
		const ScriptException &operator=(const ScriptException &) throw() = delete;

	// what
	public:
		const char *what(void) const throw() { return mWhat.c_str(); }

	// attributes
	private:
		std::string mWhat;

};
