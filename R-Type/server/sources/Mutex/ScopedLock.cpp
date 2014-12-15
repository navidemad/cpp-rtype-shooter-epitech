#include "ScopedLock.hpp"
#include "Config.hpp"
#include <map>
#include <iostream>

ScopedLock::ScopedLock(std::shared_ptr<IMutex> mutex) : mMutex(mutex) {
	mMutex->lock();
}

ScopedLock::~ScopedLock(void) {
	mMutex->unlock();
}
