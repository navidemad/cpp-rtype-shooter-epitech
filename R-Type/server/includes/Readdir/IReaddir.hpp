#pragma once

#include <list>
#include <string>

class IReaddir {

	// ctor dtor
	public:
		virtual ~IReaddir(void) {}

	// interface implementation
	public:
		virtual std::list<std::string> readFolder(const std::string&) = 0;
};
