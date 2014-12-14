#include "ScopedLock.hpp"
#include "Config.hpp"
#include <map>
#include <iostream>

static std::map<void*, uint64_t> g_mutexs;

ScopedLock::ScopedLock(std::shared_ptr<IMutex> mutex) : mMutex(mutex) {
	g_mutexs[&mMutex] = g_mutexs.count(&mMutex) > 0 ? g_mutexs[&mMutex] + 1 : 1;
	if (g_mutexs[&mMutex] > 1) {
		std::cout << std::endl << ">>>   DEADLOCK  <<<<" << std::endl << std::endl;
		std::terminate();
	}
	mMutex->lock();
}

ScopedLock::~ScopedLock(void) {
	g_mutexs[&mMutex] = g_mutexs[&mMutex] - 1;
	mMutex->unlock();
}
