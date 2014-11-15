#pragma once

#ifdef __unix__
# include <pthread.h>
#elif defined(_WIN32) || defined(WIN32)
# include <WinSock2.h>
#endif

class IMutex {

	// ctor dtor
	public:
		virtual ~IMutex(void) {}

	// interface implementation
	public:
		virtual void	lock(void) = 0;
		virtual void	unlock(void) = 0;
		virtual void	trylock(void) = 0;
        #ifdef __unix__
            virtual pthread_mutex_t	*getMutex(void) = 0;
        #elif defined(_WIN32) || defined(WIN32)
            virtual HANDLE getMutex(void) = 0;
        #endif
};
