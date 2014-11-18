#pragma once

#include <string>
#include <stdexcept>

class SocketException : public std::runtime_error {

	// default ctor dtor
	public:
		SocketException(const std::string &error);
		~SocketException(void) throw() {}
	
	// reimplementation
	public:
		const char	*what(void) const throw();

	// attributes
	private:
		std::string	mWhat;

};
