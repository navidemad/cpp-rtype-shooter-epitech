#pragma once

#include "Config.hpp"
#include "IDynLib.hpp"
#include "NoCopyable.hpp"

class WindowsDynLib : public NoCopyable, public IDynLib {

	// ctor dtor
	public:
        WindowsDynLib(void);
        ~WindowsDynLib(void);

	// interface implementation
	public:
        void    libraryLoad(const std::string&);
		void*   functionLoad(const std::string&) const;
        void    libraryFree(void);

    // internal functions
    private:
        std::wstring s2ws(const std::string& s) const;
        std::string normalize(const std::string& libraryName) const;

    // string extension
    public:
        static const std::string extension;

    // attributes
    private:
		HMODULE mDLLHandle;
};
