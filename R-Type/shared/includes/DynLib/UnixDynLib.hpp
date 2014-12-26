#pragma once

#include "IDynLib.hpp"

#include <dlfcn.h>

class UnixDynLib : public IDynLib {

	// ctor dtor
	public:
		UnixDynLib(void);
		~UnixDynLib(void);

	// copy / move operators
	public:
		UnixDynLib(const UnixDynLib &) = delete;
		UnixDynLib(const UnixDynLib &&) = delete;
		const UnixDynLib &operator=(const UnixDynLib &) = delete;
		const UnixDynLib &operator=(const UnixDynLib &&) = delete;

	// interface implementation
	public:
        void    libraryLoad(const std::string&);
		void*   functionLoad(const std::string&) const;
        void    libraryFree(void);

    // internal functions
    private:
        std::string normalize(const std::string& libraryName) const;

    // string extension
    public:
        static const std::string extension;

    // attributes
    private:
    	void *mHandle;

};
