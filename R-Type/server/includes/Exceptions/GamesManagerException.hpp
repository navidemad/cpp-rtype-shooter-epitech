#pragma once

#include <stdexcept>

class GamesManagerException : public std::runtime_error {

	// use std::runtime_error functions
	public:
		GamesManagerException(const std::string & error, const ErrorStatus &errorStatus) throw() : std::runtime_error(error), mWhat(error), mErrorStatus(errorStatus) {}
        ~GamesManagerException(void) = default;

	// copy - move operators
	public:
		const GamesManagerException &operator=(const GamesManagerException &) throw() = delete;

	// what
	public:
		const char *what(void) const throw() { return mWhat.c_str(); }
		const ErrorStatus &getErrorStatus(void) const { return mErrorStatus; }

	// attributes
	private:
		std::string mWhat;
		ErrorStatus mErrorStatus;

};
