#include "UnixCondVar.hpp"

UnixCondVar::UnixCondVar(void) {
  if (pthread_cond_init(&mCondVar, NULL) != 0)
    throw CondVarException("fail pthread_cond_init()");
}

UnixCondVar::~UnixCondVar(void) {
  if (pthread_cond_destroy(&mCondVar) != 0)
    throw CondVarException("fail pthread_cond_destroy()");
}

void UnixCondVar::wait(IMutex *mutex) {
  if (pthread_cond_wait(&mCondVar, mutex->getMutex()) != 0)
    throw CondVarException("fail pthread_cond_wait()");
}

void	UnixCondVar::signal(void) {
  if (pthread_cond_signal(&mCondVar) != 0)
    throw CondVarException("fail pthread_cond_wait()");
}

void	UnixCondVar::broadcast(void) {
  if (pthread_cond_broadcast(&mCondVar) != 0)
    throw CondVarException("fail pthread_cond_wait()");
}