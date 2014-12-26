#include "ThreadPool.hpp"
#include "ScopedLock.hpp"
#include "PortabilityBuilder.hpp"
#include "ThreadPoolException.hpp"
#include "ThreadException.hpp"
#include "CondVarException.hpp"
#include "Default.hpp"
#include <iostream>

std::shared_ptr<ThreadPool> ThreadPool::mInstance = nullptr;

ThreadPool::ThreadPool(unsigned int nbThreads)
	:	mIsRunning(true),
		mWorkers(nbThreads, nullptr),
		mMutex(PortabilityBuilder::getMutex()),
		mCondVar(PortabilityBuilder::getCondVar())
{
	for (auto &worker : mWorkers) {
		worker = PortabilityBuilder::getThread<ThreadPool *, void *>();
		try {
			worker->create(this, nullptr);
		} catch (const ThreadException& e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

ThreadPool::~ThreadPool(void) {
	stop();
}

void ThreadPool::stop(void) {
  {
    ScopedLock scopedlock(mMutex);

    if (mIsRunning == false)
      return ;

    mIsRunning = false;
  }

  mCondVar->notifyAll();
  for (const auto &worker : mWorkers)
    worker->wait();
}

void ThreadPool::operator()(void *) {
	std::function<void()> task;

	while (true) {
		{
			ScopedLock scopedlock(mMutex);

			while (mIsRunning && mTasks.empty()) {
				try {
					mCondVar->wait(mMutex);
				} catch (const CondVarException& e) {
					std::cerr << e.what() << std::endl;
				}
			}

			if (mIsRunning == false)
				return;

			task = mTasks.front();
			mTasks.pop_front();
		}

		task();
	}
}

const ThreadPool &ThreadPool::operator<<(std::function<void()> task) {
  ScopedLock scopedlock(mMutex);

  mTasks.push_back(task);
  mCondVar->notifyOne();

  return *this;
}

std::shared_ptr<ThreadPool> ThreadPool::getInstance(void) {
	if (mInstance == nullptr)
		mInstance = std::shared_ptr<ThreadPool>(new ThreadPool(Config::ThreadPool::nbThreads));

	return mInstance;
}
