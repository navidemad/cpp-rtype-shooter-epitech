#pragma once

#include "Thread/IThread.hpp"

#ifdef __unix__
# include "Thread/ThreadUnix.hpp"
#elif defined(_WIN32) || defined(WIN32)
# include "Thread/ThreadWindows.hpp"
#endif

#include <memory>

namespace Thread {

    std::shared_ptr<IThread> getInstance(void) {
        #ifdef __unix__
                return std::shared_ptr<IThread>(new ThreadUnix);
        #elif defined(_WIN32) || defined(WIN32)
                return std::shared_ptr<IThread>(new ThreadWindows);
        #endif
    }

};
