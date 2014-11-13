#include "Thread/ThreadUnix.hpp"

# include <stdexcept>
# include <string>
# include <cstring>
# include <cerrno>

ThreadUnix::ThreadUnix() {

}

ThreadUnix::~ThreadUnix() {

}

void ThreadUnix::create(void *(*start_routine)(void *), void *arg) {
    if (pthread_create(&mThread, 0, start_routine, arg) != 0)
        throw std::runtime_error(std::string("pthread_create") + strerror(errno));
}

void ThreadUnix::destroy(void) {
    if (pthread_cancel(mThread) != 0)
        throw std::runtime_error(std::string("pthread_join") + strerror(errno));
}

void ThreadUnix::join(void) {
    if (pthread_join(mThread, 0) != 0)
        throw std::runtime_error(std::string("pthread_join") + strerror(errno));
}
