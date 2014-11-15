#pragma once

#include <stdexcept>

class SocketException : public std::runtime_error {

	// use std::runtime_error functions
	public:
	using std::runtime_error::runtime_error;
		using std::runtime_error::what;

};
