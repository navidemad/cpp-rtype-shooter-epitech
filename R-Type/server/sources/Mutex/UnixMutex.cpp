#include "UnixMutex.hpp"

UnixMutex::UnixMutex(void) {
  if (pthread_mutex_init(&mMutex, NULL) != 0)
    throw MutexException("fail pthread_mutex_init()");
}

UnixMutex::~UnixMutex(void) {
  if (pthread_mutex_destroy(&mMutex) != 0)
    throw MutexException("fail pthread_mutex_destroy()");
}

void	UnixMutex::lock(void) {
  if (pthread_mutex_lock(&mMutex) != 0)
    throw MutexException("fail pthread_mutex_lock()");
}

void	UnixMutex::unlock(void) {
  if (pthread_mutex_unlock(&mMutex) != 0)
    throw MutexException("fail pthread_mutex_unlock()");
}

void	UnixMutex::trylock(void) {
  if(pthread_mutex_trylock(&mMutex) != 0)
    throw MutexException("fail pthread_mutex_trylock()");
}
