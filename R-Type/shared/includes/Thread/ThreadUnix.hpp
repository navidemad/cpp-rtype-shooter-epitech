#pragma once

#include "Thread/IThread.hpp"
#include <pthread.h>

class ThreadUnix : public IThread
{
public:
    ThreadUnix(void);
    virtual ~ThreadUnix(void);
    const ThreadUnix & operator = (const ThreadUnix &) = delete;
    ThreadUnix(const ThreadUnix &) = delete;
public:
    void create(void *(*start_routine)(void *), void *arg);
    void destroy();
    void join();
private:
    pthread_t mThread;
};
