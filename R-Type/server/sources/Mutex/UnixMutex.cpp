#include "UnixMutex.hpp"

UnixMutex::UnixMutex(void) {
  if (pthread_mutex_init(&mMutex, 0) != UnixMutex::PTHREAD_MUTEX_SUCCESS)
    throw MutexException("fail pthread_mutex_init()");
}

UnixMutex::~UnixMutex(void) {
  if (pthread_mutex_destroy(&mMutex) != UnixMutex::PTHREAD_MUTEX_SUCCESS)
    throw MutexException("fail pthread_mutex_destroy()");
}

void	UnixMutex::lock(void) {
  if (pthread_mutex_lock(&mMutex) != UnixMutex::PTHREAD_MUTEX_SUCCESS)
    throw MutexException("fail pthread_mutex_lock()");
}

void	UnixMutex::unlock(void) {
  if (pthread_mutex_unlock(&mMutex) != UnixMutex::PTHREAD_MUTEX_SUCCESS)
    throw MutexException("fail pthread_mutex_unlock()");
}

void	UnixMutex::trylock(void) {
  if(pthread_mutex_trylock(&mMutex) != UnixMutex::PTHREAD_MUTEX_SUCCESS)
    throw MutexException("fail pthread_mutex_trylock()");
}
