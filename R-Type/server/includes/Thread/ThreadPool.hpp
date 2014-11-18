#pragma once

#include "IThread.hpp"
#include "IMutex.hpp"
#include "ICondVar.hpp"
#include <vector>
#include <deque>
#include <functional>
#include <memory>

class ThreadPool {

	// ctor dtor
	public:
		ThreadPool(unsigned int nbThread);
		~ThreadPool(void);

	// copy / move operators
	public:
		ThreadPool(const ThreadPool &) = delete;
		ThreadPool(const ThreadPool &&) = delete;
		const ThreadPool &operator=(const ThreadPool &) = delete;
		const ThreadPool &operator=(const ThreadPool &&) = delete;

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
		std::unique_ptr<ICondVar> mCondVar;

};
