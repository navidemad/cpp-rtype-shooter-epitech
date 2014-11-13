#pragma once

#include "Thread/IThread.hpp"
#include <windows.h>

class ThreadWindows : public IThread
{
public:
    ThreadWindows(void);
    virtual ~ThreadWindows(void);
    const ThreadWindows & operator = (const ThreadWindows &) = delete;
    ThreadWindows(const ThreadWindows &) = delete;
public:
    void create(void *(*start_routine)(void *), void *arg);
    void destroy();
    void join();
private:
    HANDLE mThread;
};
