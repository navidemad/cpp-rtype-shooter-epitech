#pragma once

// Forward declaration class
template <typename U, typename T>
class IThread;

// Trampoline function
template <typename U, typename T>
void *start_thread_trampoline(void *arg) {
  reinterpret_cast<IThread<U, T> *>(arg)->start();
  return NULL;
}

// Thread Abstraction Template
template <typename U, typename T>
class IThread
{
public:
    virtual ~IThread() {}
  	virtual void create(U callObj, T fctParam) = 0;
    virtual void wait(void **retVal) = 0;
  	virtual void *start(void) = 0;
    virtual void cancel(void) = 0;
    virtual void exit(void *status) = 0;
};