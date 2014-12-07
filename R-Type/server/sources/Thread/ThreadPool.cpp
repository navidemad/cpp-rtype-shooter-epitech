#include "ThreadPool.hpp"
#include "ScopedLock.hpp"
#include "PortabilityBuilder.hpp"
#include "ThreadPoolException.hpp"

ThreadPool::ThreadPool(unsigned int nbThreads)
	:	mIsRunning(true),
		mWorkers(nbThreads, nullptr),
		mMutex(PortabilityBuilder::getMutex()),
		mCondVar(PortabilityBuilder::getCondVar())
{
	for (auto &worker : mWorkers) {
		worker = PortabilityBuilder::getThread<ThreadPool *, void *>();
		worker->create(this, nullptr);
	}
}

ThreadPool::~ThreadPool(void) {
	stop();
}

void ThreadPool::stop(void) {
	{
        ScopedLock scopedLock(mMutex);

    if (mIsRunning == false)
    	return ;

		mIsRunning = false;
		mCondVar->notifyAll();
	}

	for (const auto &worker : mWorkers)
		worker->cancel();
}

void ThreadPool::operator()(void *) {
	std::function<void()> task;

	while (true) {
		{
			ScopedLock scopedLock(mMutex);

			while (mIsRunning && mTasks.empty())
				mCondVar->wait(mMutex);

			if (mIsRunning == false)
				return;

			task = mTasks.front();
			mTasks.pop_front();
		}

		task();
	}
}

const ThreadPool &ThreadPool::operator<<(std::function<void()> task) {
	ScopedLock scopedLock(mMutex);

	mTasks.push_back(task);
	mCondVar->notifyOne();

	return *this;
}

std::shared_ptr<ThreadPool> ThreadPool::getInstance(void) {
	static std::shared_ptr<ThreadPool> instance(new ThreadPool(ThreadPool::NB_THREADS));

	return instance;
}
