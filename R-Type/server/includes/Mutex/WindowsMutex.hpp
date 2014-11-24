#pragma once

#include "IMutex.hpp"
#include <WinSock2.h>
#include "MutexException.hpp"

class WindowsMutex : public IMutex {

	// ctor dtor
	public:
		explicit WindowsMutex(void);
		~WindowsMutex(void);

	// copy / move operators
	public:
		WindowsMutex(const WindowsMutex &) = delete;
		WindowsMutex(WindowsMutex &&) = delete;
		const WindowsMutex &operator=(const WindowsMutex &) = delete;
		const WindowsMutex &operator=(WindowsMutex &&) = delete;

	// interface implementation
	public:
		void	lock(void);
		void	unlock(void);
		void	trylock(void);
        void	*getMutex(void);

    // attributes
    private:
        CRITICAL_SECTION mMutex;
        bool    mAlreadyLocked;
};
