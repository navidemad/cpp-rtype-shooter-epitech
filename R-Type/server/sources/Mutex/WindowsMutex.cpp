#include "WindowsMutex.hpp"

WindowsMutex::WindowsMutex(void) {
    if ((mMutex = CreateMutex(0, FALSE, 0)) == 0)
        throw MutexException("fail CreateMutex()");
}

WindowsMutex::~WindowsMutex(void) {
    if (CloseHandle(mMutex) == 0)
        throw MutexException("fail CloseHandle()");
}

void	WindowsMutex::lock(void) {
    DWORD ret = WaitForSingleObject(mMutex, INFINITE);
	
	if (ret == WAIT_ABANDONED || ret == WAIT_TIMEOUT || ret == WAIT_FAILED)
        throw MutexException("fail WaitForSingleObject()");
}

void	WindowsMutex::unlock(void) {
    if (ReleaseMutex(mMutex) == 0)
        throw MutexException("fail ReleaseMutex()");
}

void	WindowsMutex::trylock(void) {
    DWORD ret = WaitForSingleObject(mMutex, 0);

    if (ret == WAIT_ABANDONED || ret == WAIT_TIMEOUT || ret == WAIT_FAILED)
        throw MutexException("fail WaitForSingleObject()");
}
