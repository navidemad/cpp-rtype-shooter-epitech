#pragma once

#include "IMutex.hpp"
#include "MutexException.hpp"
#include "NoCopyable.hpp"

#include <WinSock2.h>

class WindowsMutex : public NoCopyable, public IMutex {

	// ctor dtor
	public:
		WindowsMutex(void);
		~WindowsMutex(void);

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
