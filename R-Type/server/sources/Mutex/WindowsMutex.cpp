#include "WindowsMutex.hpp"

WindowsMutex::WindowsMutex(void) : mAlreadyLocked(false) {
    InitializeCriticalSection(&mMutex);
}

WindowsMutex::~WindowsMutex(void) {
    DeleteCriticalSection(&mMutex);
}

void	WindowsMutex::lock(void) {
    EnterCriticalSection(&mMutex);
    mAlreadyLocked = true;
}

void	WindowsMutex::unlock(void) {
    LeaveCriticalSection(&mMutex);
    mAlreadyLocked = false;
}

void	WindowsMutex::trylock(void) {
    if (TryEnterCriticalSection(&mMutex) && mAlreadyLocked)
        LeaveCriticalSection(&mMutex);
}

void *WindowsMutex::getMutex(void) {
    return &mMutex;
}
