#include "Mutex.hpp"

void	Mutex::lock(void) {
	mQMutex.lock();
}

bool	Mutex::tryLock(int milliseconds) {
	return mQMutex.tryLock(milliseconds);
}

void	Mutex::unlock(void) {
	mQMutex.unlock();
}
