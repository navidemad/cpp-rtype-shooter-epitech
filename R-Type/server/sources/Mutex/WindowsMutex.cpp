#include "WindowsMutex.hpp"
#include "MutexException.hpp"

WindowsMutex::WindowsMutex(void) {
	mMutex = CreateMutex(NULL, FALSE, NULL);

	if (mMutex == NULL)
		MutexException("Cannot create mutex (fail CreateMutex())");
}

WindowsMutex::~WindowsMutex(void) {
	CloseHandle(mMutex);
}

void	WindowsMutex::lock(void) {
	if (WaitForSingleObject(mMutex, INFINITE) != WAIT_OBJECT_0)
		MutexException("Fail WaitForSingleObject() (Mutex::lock())");
}

void	WindowsMutex::unlock(void) {
	ReleaseMutex(mMutex);
}

void	WindowsMutex::trylock(void) {
	if (WaitForSingleObject(mMutex, 0) != WAIT_OBJECT_0)
		MutexException("Fail WaitForSingleObject() (Mutex::lock())");
}

void *WindowsMutex::getMutex(void) {
    return &mMutex;
}
