#pragma once

#include "IMutex.hpp"

class ScopedLock {

	// ctor - dtor
	public:
		ScopedLock(IMutex *mutex);
		~ScopedLock(void);

	// attributes
	private:
		IMutex	*mMutex;

};
