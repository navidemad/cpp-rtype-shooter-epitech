#include "WindowsMutex.hpp"

WindowsMutex::WindowsMutex(void) : mAlreadyLocked(false) {
    InitializeCriticalSection(&mMutex);
}

WindowsMutex::~WindowsMutex(void) {
    DeleteCriticalSection(&mMutex);
}

void	WindowsMutex::lock(void) {
    EnterCriticalSection(&mMutex);
    while (mAlreadyLocked) Sleep(1000);
    mAlreadyLocked = true;
}

void	WindowsMutex::unlock(void) {
    mAlreadyLocked = false;
    LeaveCriticalSection(&mMutex);
}

void	WindowsMutex::trylock(void) {
    if (TryEnterCriticalSection(&mMutex) && mAlreadyLocked)
    LeaveCriticalSection(&mMutex);
}

void *WindowsMutex::getMutex(void) {
    return &mMutex;
}
