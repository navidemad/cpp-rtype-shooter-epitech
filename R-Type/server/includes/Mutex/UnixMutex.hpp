#pragma once

#include "IMutex.hpp"
#include <pthread.h>
#include "MutexException.hpp"

class UnixMutex : public IMutex {

	// ctor dtor
	public:
		UnixMutex(void);
		~UnixMutex(void);

	// copy / move operators
	public:
		UnixMutex(const UnixMutex &) = delete;
		UnixMutex(const UnixMutex &&) = delete;
		const UnixMutex &operator=(const UnixMutex &) = delete;
		const UnixMutex &operator=(const UnixMutex &&) = delete;

	// interface implementation
	public:
		void	lock(void);
		void	unlock(void);
		void	trylock(void);
		void	*getMutex(void);

	// 
	public:
	  enum : unsigned char { PTHREAD_MUTEX_SUCCESS = 0 };

	// attributes
	private:
		pthread_mutex_t	mMutex;

};
