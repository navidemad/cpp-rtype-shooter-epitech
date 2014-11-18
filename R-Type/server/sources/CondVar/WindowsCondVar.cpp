#include "WindowsCondVar.hpp"

WindowsCondVar::WindowsCondVar(void) : mWaitersCount(0) {
    if ((mEvents[_CONDITION_EVENT_ONE] = CreateEvent(NULL, FALSE, FALSE, NULL)) == 0)
        throw CondVarException("fail CreateEvent()");

    if ((mEvents[_CONDITION_EVENT_ALL] = CreateEvent(NULL, TRUE, FALSE, NULL)) == 0)
        throw CondVarException("fail CreateEvent()");
    
    // Initialize the critical section
    InitializeCriticalSection(&mWaitersCountLock);
}

WindowsCondVar::~WindowsCondVar(void) {
    if (CloseHandle(mEvents[_CONDITION_EVENT_ONE]) == 0)
        throw CondVarException("fail CloseHandle()");

    if (CloseHandle(mEvents[_CONDITION_EVENT_ALL]) == 0)
        throw CondVarException("fail CloseHandle()");
    CloseHandle(mEvents[_CONDITION_EVENT_ALL]);

    // Release resources used by the critical section object.
    DeleteCriticalSection(&mWaitersCountLock);
}

void WindowsCondVar::wait(std::shared_ptr<IMutex> mutex) {
    // Request ownership of the critical section.
    EnterCriticalSection(&mWaitersCountLock);

    ++mWaitersCount;

    // Release ownership of the critical section.
    LeaveCriticalSection(&mWaitersCountLock);

    // Release the mutex while waiting for the condition (will decrease the number of waiters when done)
    mutex->unlock();
    _wait();
    mutex->lock();
};

void WindowsCondVar::_wait(void) {
    int result = WaitForMultipleObjects(2, mEvents, FALSE, INFINITE);

    // Request ownership of the critical section.
    EnterCriticalSection(&mWaitersCountLock);

    --mWaitersCount;
    bool lastWaiter = (result == (WAIT_OBJECT_0 + _CONDITION_EVENT_ALL)) &&
                    (mWaitersCount == 0);

    // Release ownership of the critical section.
    LeaveCriticalSection(&mWaitersCountLock);

    if (lastWaiter)
        ResetEvent(mEvents[_CONDITION_EVENT_ALL]);
}

void	WindowsCondVar::notifyOne(void) {
    // Request ownership of the critical section.
    EnterCriticalSection(&mWaitersCountLock);

    bool haveWaiters = (mWaitersCount > 0);

    // Release ownership of the critical section.
    LeaveCriticalSection(&mWaitersCountLock);

    if (haveWaiters && SetEvent(mEvents[_CONDITION_EVENT_ONE]) == 0)
            throw CondVarException("fail SetEvent()");
}

void	WindowsCondVar::notifyAll(void) {
    // Request ownership of the critical section.
    EnterCriticalSection(&mWaitersCountLock);

    bool haveWaiters = (mWaitersCount > 0);

    // Release ownership of the critical section.
    LeaveCriticalSection(&mWaitersCountLock);

    if (haveWaiters && SetEvent(mEvents[_CONDITION_EVENT_ALL]) == 0)
        throw CondVarException("fail SetEvent()");
}
