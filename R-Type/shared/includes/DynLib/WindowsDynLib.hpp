#pragma once

#include "Config.hpp"
#include "IDynLib.hpp"
#include "NoCopyable.hpp"

#define DLL_IMPORT __declspec(dllimport)

class WindowsDynLib : public NoCopyable, public IDynLib {

	// ctor dtor
	public:
        WindowsDynLib(void) = default;
        ~WindowsDynLib(void) = default;

	// interface implementation
	public:
        void    libraryLoad(const std::string&);
		void*   functionLoad(const std::string&);
        void    libraryFree(void);

    // internal functions
    private:
        std::wstring s2ws(const std::string& s);
        std::string normalize(const std::string& libraryName);

    // string extension
    public:
        static const std::string extension;

    // attributes
    private:
		HMODULE mDLLHandle;
};
