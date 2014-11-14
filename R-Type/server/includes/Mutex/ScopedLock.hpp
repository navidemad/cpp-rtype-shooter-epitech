#pragma once

#include "IMutex.hpp"

class ScopedLock {

	// ctor dtor
	public:
		ScopedLock(IMutex *);
		~ScopedLock(void);

	// copy / move operators
	public:
		ScopedLock(const ScopedLock &) = delete;
		ScopedLock(const ScopedLock &&) = delete;
		const ScopedLock &operator=(const ScopedLock &) = delete;
		const ScopedLock &operator=(const ScopedLock &&) = delete;

	// attributes
	private:
		IMutex	*mMutex;

};
