#pragma once

#include <stdexcept>
#include "ErrorStatus.hpp"

class GameException : public std::runtime_error {

	// use std::runtime_error functions
	public:
		GameException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) {}
		~GameException(void) {}

	// copy - move operators
	public:
		const GameException &operator=(const GameException &) throw() = delete;

	// what
	public:
		const char *what(void) const throw() { return mWhat.c_str(); }

	// attributes
	private:
		std::string mWhat;

};
