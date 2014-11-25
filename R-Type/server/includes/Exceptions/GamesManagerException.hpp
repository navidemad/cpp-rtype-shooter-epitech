#pragma once

#include <stdexcept>

class GamesManagerException : public std::runtime_error {

	// use std::runtime_error functions
	public:
		GamesManagerException(const std::string & error) throw() : std::runtime_error(error), mWhat(error) {}
		~GamesManagerException(void) {}

	// copy - move operators
	public:
		const GamesManagerException &operator=(const GamesManagerException &) throw() = delete;

	// what
	public:
		const char *what(void) const throw() { return mWhat.c_str(); }

	// attributes
	private:
		std::string mWhat;

};
