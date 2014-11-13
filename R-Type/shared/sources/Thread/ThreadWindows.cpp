#include "Thread/ThreadWindows.hpp"

#include <system_error>

ThreadWindows::ThreadWindows() {

}

ThreadWindows::~ThreadWindows() {

}

void ThreadWindows::create(void *(*start_routine)(void *), void *arg) {
    mThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)start_routine, (LPVOID)arg, 0, 0);
    if (mThread == NULL) {
        DWORD dwErrVal = GetLastError();
        std::error_code ec(dwErrVal, std::system_category());
        throw std::system_error(ec, "Exception occurred");
    }
}

void ThreadWindows::destroy(void) {
    if (TerminateThread(mThread, -1) == 0) {
        DWORD dwErrVal = GetLastError();
        std::error_code ec(dwErrVal, std::system_category());
        throw std::system_error(ec, "Exception occurred");
    }
}

void ThreadWindows::join(void) {
    WaitForSingleObject(mThread, INFINITE);
}
