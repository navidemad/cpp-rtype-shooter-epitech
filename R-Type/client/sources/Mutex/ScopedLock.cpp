#include "ScopedLock.hpp"

ScopedLock::ScopedLock(IMutex *mutex)
	: mMutex(mutex)
{
	mMutex->lock();
}

ScopedLock::~ScopedLock(void) {
	mMutex->unlock();
}
