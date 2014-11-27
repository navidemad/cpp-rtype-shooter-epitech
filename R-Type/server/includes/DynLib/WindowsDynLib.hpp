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
        void    libraryLoad(std::string&);
		void*   functionLoad(const std::string&);
        void    libraryFree(void);

    // internal functions
    private:
        std::wstring s2ws(const std::string& s);

    // string extension
    public:
        static const std::string extension;

    // attributes
    private:
    	HINSTANCE mDLLHandle;
};
