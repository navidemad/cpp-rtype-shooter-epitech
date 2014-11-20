#include "PortabilityBuilder.hpp"
#include "WindowsCondVar.hpp"
#include "CondVarException.hpp"
#include "ScopedLock.hpp"

WindowsCondVar::WindowsCondVar(void) : mWaitersCount(0), mWaitersCountLock(PortabilityBuilder::getMutex()) {
    if ((mEvents[WindowsCondVar::Event::SIGNAL] = CreateEvent(NULL,  // no security
        FALSE, // auto-reset event
        FALSE, // non-signaled initially
        NULL) // unnamed
        ) == 0) throw CondVarException("fail CreateEvent()");

    if ((mEvents[WindowsCondVar::Event::BROADCAST] = CreateEvent(NULL,  // no security
        TRUE,  // manual-reset
        FALSE, // non-signaled initially
        NULL) // unnamed
        ) == 0) throw CondVarException("fail CreateEvent()");
}

WindowsCondVar::~WindowsCondVar(void) {
    if (CloseHandle(mEvents[WindowsCondVar::Event::SIGNAL]) == 0)
        throw CondVarException("fail CloseHandle() for Event::ONE");

    if (CloseHandle(mEvents[WindowsCondVar::Event::BROADCAST]) == 0)
        throw CondVarException("fail CloseHandle() for Event::ALL");

    CloseHandle(mEvents[WindowsCondVar::Event::BROADCAST]);
}

void WindowsCondVar::wait(std::shared_ptr<IMutex> externalMutex) {

    { ScopedLock scopedLock(mWaitersCountLock); 
        ++mWaitersCount; }

    externalMutex->unlock();

    int result = WaitForMultipleObjects(WindowsCondVar::Event::MAX_EVENTS, mEvents, FALSE, INFINITE);
    bool lastWaiter;

    { ScopedLock scopedLock(mWaitersCountLock);
        --mWaitersCount;
        lastWaiter = result == WAIT_OBJECT_0 + WindowsCondVar::Event::BROADCAST && mWaitersCount == 0;
    }

    if (lastWaiter)
        ResetEvent(mEvents[WindowsCondVar::Event::BROADCAST]);

    externalMutex->lock();
};

void	WindowsCondVar::notifyOne(void) {

    bool haveWaiters;

    { ScopedLock scopedLock(mWaitersCountLock);
        haveWaiters = (mWaitersCount > 0);
    }

    if (haveWaiters && SetEvent(mEvents[WindowsCondVar::Event::SIGNAL]) == 0)
            throw CondVarException("fail SetEvent()");
}

void	WindowsCondVar::notifyAll(void) {

    bool haveWaiters;

    { ScopedLock scopedLock(mWaitersCountLock);
    haveWaiters = (mWaitersCount > 0);
    }

    if (haveWaiters && SetEvent(mEvents[WindowsCondVar::Event::BROADCAST]) == 0)
        throw CondVarException("fail SetEvent()");
}
