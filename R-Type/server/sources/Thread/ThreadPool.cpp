#include "ThreadPool.hpp"
#include "ScopedLock.hpp"
#include "PortabilityBuilder.hpp"
#include "ThreadPoolException.hpp"
#include "ThreadException.hpp"
#include "CondVarException.hpp"
#include "Default.hpp"
#include <iostream>

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
        Scopedlock(mMutex);

    if (mIsRunning == false)
    	return ;

		mIsRunning = false;
		try {
			mCondVar->notifyAll();
		} catch (const CondVarException& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	mWorkers.clear();
}

void ThreadPool::operator()(void *) {
	std::function<void()> task;

	while (true) {
		{
			Scopedlock(mMutex);

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
	Scopedlock(mMutex);

	mTasks.push_back(task);
	try {
		mCondVar->notifyOne();
	} catch (const CondVarException& e) {
		std::cerr << e.what() << std::endl;
	}

	return *this;
}

std::shared_ptr<ThreadPool> ThreadPool::getInstance(void) {
    static std::shared_ptr<ThreadPool> instance(new ThreadPool(Config::ThreadPool::nbThreads));
    //static std::shared_ptr<ThreadPool> instance = std::make_shared<ThreadPool>(Config::ThreadPool::nbThreads);

	return instance;
}
