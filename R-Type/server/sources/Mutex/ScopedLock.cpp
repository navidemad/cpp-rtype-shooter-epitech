#include "ScopedLock.hpp"

ScopedLock::ScopedLock(std::shared_ptr<IMutex> mutex) : mMutex(mutex) {
	mMutex.get()->lock();
}

ScopedLock::~ScopedLock(void) {
	mMutex.get()->unlock();
}
