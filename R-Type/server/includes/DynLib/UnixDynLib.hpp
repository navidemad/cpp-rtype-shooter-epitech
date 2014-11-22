#pragma once

#include "IDynLib.hpp"

#include <dlfcn.h>

#define EXT ".so"

class UnixDynLib : public IDynLib {

	// ctor dtor
	public:
		UnixDynLib(void) = default;
		~UnixDynLib(void) = default;

	// copy / move operators
	public:
		UnixDynLib(const UnixDynLib &) = delete;
		UnixDynLib(const UnixDynLib &&) = delete;
		const UnixDynLib &operator=(const UnixDynLib &) = delete;
		const UnixDynLib &operator=(const UnixDynLib &&) = delete;

	// interface implementation
	public:
        void    libraryLoad(std::string&);
		void*   functionLoad(const std::string&);
        void    libraryFree(void);

    // attributes
    private:
    	void *mHandle;

};
