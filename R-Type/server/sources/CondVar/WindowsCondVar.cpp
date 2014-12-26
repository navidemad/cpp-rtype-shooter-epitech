#include "PortabilityBuilder.hpp"
#include "WindowsCondVar.hpp"
#include "CondVarException.hpp"
#include "ScopedLock.hpp"

WindowsCondVar::WindowsCondVar(void) : mWaitersCount(0), mWaitersCountLock(PortabilityBuilder::getMutex()) {
    if ((mEvents[WindowsCondVar::Event::SIGNAL] = CreateEvent(NULL,  // no security
        FALSE, // auto-reset event
        FALSE, // non-signaled initially
        NULL) // unnamed
        ) == 0) throw CondVarException("fail CreateEvent(SIGNAL)");

    if ((mEvents[WindowsCondVar::Event::BROADCAST] = CreateEvent(NULL,  // no security
        TRUE,  // manual-reset
        FALSE, // non-signaled initially
        NULL) // unnamed
        ) == 0) throw CondVarException("fail CreateEvent(BROADCAST)");
}

WindowsCondVar::~WindowsCondVar(void) {

    if (mEvents[WindowsCondVar::Event::SIGNAL] && !CloseHandle(mEvents[WindowsCondVar::Event::SIGNAL]))
        throw CondVarException("fail CloseHandle(SIGNAL)");

    if (mEvents[WindowsCondVar::Event::BROADCAST] && !CloseHandle(mEvents[WindowsCondVar::Event::BROADCAST]))
        throw CondVarException("fail CloseHandle(BROADCAST)");
}

void WindowsCondVar::wait(const std::shared_ptr<IMutex> &externalMutex) {

    { ScopedLock scopedlock(mWaitersCountLock);
        ++mWaitersCount; }

    externalMutex->unlock();

    int result;
    if ((result = WaitForMultipleObjects(WindowsCondVar::Event::MAX_EVENTS, mEvents, FALSE, INFINITE)) == WAIT_FAILED)
        throw CondVarException("fail WaitForMultipleObjects()");

    bool lastWaiter;

    { ScopedLock scopedlock(mWaitersCountLock);
        --mWaitersCount;
        lastWaiter = result == WAIT_OBJECT_0 + WindowsCondVar::Event::BROADCAST && mWaitersCount == 0;
    }

    if (lastWaiter && !ResetEvent(mEvents[WindowsCondVar::Event::BROADCAST]))
       throw CondVarException("fail ResetEvent()");

    externalMutex->lock();

    if (result == WAIT_TIMEOUT)
        throw CondVarException("fail win32 wait failed");
};

void	WindowsCondVar::notifyOne(void) {

    bool haveWaiters;

    { ScopedLock scopedlock(mWaitersCountLock);
        haveWaiters = (mWaitersCount > 0);
    }

    if (haveWaiters && !SetEvent(mEvents[WindowsCondVar::Event::SIGNAL]))
        throw CondVarException("fail SetEvent()");
}

void	WindowsCondVar::notifyAll(void) {

    bool haveWaiters;

    { ScopedLock scopedlock(mWaitersCountLock);
    haveWaiters = (mWaitersCount > 0);
    }

    if (haveWaiters && !SetEvent(mEvents[WindowsCondVar::Event::BROADCAST]))
        throw CondVarException("fail SetEvent()");
}
