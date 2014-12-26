#include "ScopedLock.hpp"

ScopedLock::ScopedLock(std::shared_ptr<IMutex> mutex) : mMutex(mutex) {
	mMutex->lock();
}

ScopedLock::~ScopedLock(void) {
	mMutex->unlock();
}
