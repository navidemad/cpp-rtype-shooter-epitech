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

enum class State;

// Thread Abstraction Template
template <typename U, typename T>
class IThread
{
public:
  enum State : unsigned char 
  {
      NOT_CREATED,
      IN_EXECUTION,
      HAS_FINISHED
  };
public:
    virtual ~IThread() {}
    virtual State getState(void) const;
  	virtual void create(U callObj, T fctParam);
  	virtual void wait(void *retVal);
  	virtual void *start(void);
};