#pragma once

#include <list>
#include <string>

class IReaddir {

	// ctor dtor
	public:
        virtual ~IReaddir(void) = default;

	// interface implementation
	public:
		virtual std::list<std::string> readFolder(const std::string&) const = 0;
};
