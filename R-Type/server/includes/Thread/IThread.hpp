#pragma once

// Forward declaration class
template <typename U, typename T>
class IThread;

// Trampoline function
template <typename U, typename T>
void *start_thread_trampoline(void *arg) {
  reinterpret_cast<IThread<U, T> *>(arg)->start();
  return 0;
}

namespace Thread
{
  enum State
  {
      NOT_CREATED,
      IN_EXECUTION,
      HAS_FINISHED
  };
}

// Thread Abstraction Template
template <typename U, typename T>
class IThread
{
public:
    virtual ~IThread() {}
    virtual Thread::State getState(void) const = 0;
  	virtual void create(U callObj, T fctParam) = 0;
  	virtual void wait(void *retVal) = 0;
  	virtual void *start(void) = 0;
};