#include "UnixCondVar.hpp"

UnixCondVar::UnixCondVar(void) {
  if (pthread_cond_init(&mCondVar, NULL) != 0)
    throw CondVarException("fail pthread_cond_init()");
}

UnixCondVar::~UnixCondVar(void) {
  if (pthread_cond_destroy(&mCondVar) != 0)
    throw CondVarException("fail pthread_cond_destroy()");
}

void UnixCondVar::wait(const std::shared_ptr<IMutex> &mutex) {
  if (pthread_cond_wait(&mCondVar, reinterpret_cast<pthread_mutex_t *>(mutex->getMutex())) != 0)
    throw CondVarException("fail pthread_cond_wait()");
}

void	UnixCondVar::notifyOne(void) {
  if (pthread_cond_signal(&mCondVar) != 0)
    throw CondVarException("fail pthread_cond_wait()");
}

void	UnixCondVar::notifyAll(void) {
  if (pthread_cond_broadcast(&mCondVar) != 0)
    throw CondVarException("fail pthread_cond_wait()");
}
