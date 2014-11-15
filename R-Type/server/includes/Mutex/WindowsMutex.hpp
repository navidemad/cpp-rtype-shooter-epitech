#pragma once

#include "IMutex.hpp"
#include <windows.h>
#include "MutexException.hpp"
#pragma comment(lib, "Ws2_32.lib")

class WindowsMutex : public IMutex {

	// ctor dtor
	public:
		WindowsMutex(void);
		~WindowsMutex(void);

	// copy / move operators
	public:
		WindowsMutex(const WindowsMutex &) = delete;
		WindowsMutex(const WindowsMutex &&) = delete;
		const WindowsMutex &operator=(const WindowsMutex &) = delete;
		const WindowsMutex &operator=(const WindowsMutex &&) = delete;

	// interface implementation
	public:
		void	lock(void);
		void	unlock(void);
		void	trylock(void);
        HANDLE getMutex(void) const;

    // attributes
    private:
        HANDLE	mMutex;
};
