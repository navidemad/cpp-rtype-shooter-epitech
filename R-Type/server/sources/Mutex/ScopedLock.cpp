#include "ScopedLock.hpp"

ScopedLock::ScopedLock(std::shared_ptr<IMutex> mutex, const char* /*callerFunctionName*/, const char* /*callerFile*/, const unsigned long /*callerLine*/) : mMutex(mutex) {
	mMutex->lock();
}

ScopedLock::~ScopedLock(void) {
	mMutex->unlock();
}
