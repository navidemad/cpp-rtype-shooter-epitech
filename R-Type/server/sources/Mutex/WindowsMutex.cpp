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
    if (WaitForSingleObject(mMutex, INFINITE) != WAIT_OBJECT_0)
        throw MutexException("fail WaitForSingleObject()");
}

void	WindowsMutex::unlock(void) {
    if (ReleaseMutex(mMutex) == 0)
        throw MutexException("fail ReleaseMutex()");
}

void	WindowsMutex::trylock(void) {
    if (WaitForSingleObject(mMutex, 0) != WAIT_OBJECT_0)
        throw MutexException("fail WaitForSingleObject()");
}

void *WindowsMutex::getMutex(void) {
    return &mMutex;
}
