#include "WindowsCondVar.hpp"

WindowsCondVar::WindowsCondVar(void) {
    if ((mCondVar = CreateEvent(0, FALSE, FALSE, 0)) == 0)
        throw CondVarException("fail CreateEvent()");
}

WindowsCondVar::~WindowsCondVar(void) {
    if (CloseHandle(mCondVar) == 0)
        throw CondVarException("fail CloseHandle()");
}

void WindowsCondVar::wait(std::shared_ptr<IMutex> mutex) {
    if (SignalObjectAndWait(reinterpret_cast<HANDLE>(mutex->getMutex()), mCondVar, INFINITE, FALSE) != WAIT_OBJECT_0 ||
		WaitForSingleObject(reinterpret_cast<HANDLE>(mutex->getMutex()), INFINITE) != WAIT_OBJECT_0)
        throw CondVarException("fail WaitForSingleObject()");
};

void	WindowsCondVar::signal(void) {
    if (SetEvent(mCondVar) == 0)
        throw CondVarException("fail SetEvent()");
}

void	WindowsCondVar::broadcast(void) {
    if (PulseEvent(mCondVar) == 0)
        throw CondVarException("fail PulseEvent()");
}
