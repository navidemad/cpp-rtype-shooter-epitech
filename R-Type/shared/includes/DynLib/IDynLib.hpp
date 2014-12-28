#pragma once

#include <string>

class IDynLib {

	// ctor dtor
	public:
        virtual ~IDynLib(void) = default;

	// interface implementation
	public:
        virtual void    libraryLoad(const std::string&) = 0;
		virtual void*   functionLoad(const std::string&) const = 0;
        virtual void    libraryFree(void) = 0;

};
