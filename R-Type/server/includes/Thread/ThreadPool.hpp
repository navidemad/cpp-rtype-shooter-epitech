#pragma once

#include "IThread.hpp"
#include "IMutex.hpp"
#include "ICondVar.hpp"
#include <vector>
#include <deque>
#include <functional>
#include <memory>

class ThreadPool {

	// ctor - dtor
	private:
		explicit ThreadPool(unsigned int nbThreads);
	public:
		~ThreadPool(void);

	// copy / move operators
	public:
		ThreadPool(const ThreadPool &) = delete;
		ThreadPool(ThreadPool &&) = delete;
		const ThreadPool &operator=(const ThreadPool &) = delete;
		const ThreadPool &operator=(ThreadPool &&) = delete;

	// singleton handle instance
	public:
		static std::shared_ptr<ThreadPool> getInstance(void);

	// nb threads
	public:
		static const unsigned int NB_THREADS = 6;

	// handle tasks
	public:
		const ThreadPool	&operator<<(std::function<void()> task);
		void				operator()(void *);

	// attributes
	private:
		bool mIsRunning;
		std::vector<std::shared_ptr<IThread<ThreadPool *, void *>>> mWorkers;
		std::deque<std::function<void()>> mTasks;
        std::shared_ptr<IMutex> mMutex;
		std::shared_ptr<ICondVar> mCondVar;

};
