#pragma once

#include "Thread/IThread.hpp"
#include "Thread/ThreadUnix.hpp"
#include "Thread/ThreadWindows.hpp"

#include <memory>

struct Thread
{
    Thread(void) {}
    virtual ~Thread(void) {}
    const Thread & operator = (const Thread &) = delete;
    Thread(const Thread &) = delete;
    static std::shared_ptr<IThread> Thread::getInstance()
    {
        #ifdef __unix__
                return std::shared_ptr<IThread>(new ThreadUnix);
        #elif defined(_WIN32) || defined(WIN32)
                return std::shared_ptr<IThread>(new ThreadWindows);
        #endif
    }
};
