#include "ScopedLock.hpp"
#include "Config.hpp"
#include <map>
#include <iostream>

std::map<void*, uint64_t> g_mutexs;

ScopedLock::ScopedLock(std::shared_ptr<IMutex> mutex) : mMutex(mutex) {
	if (g_mutexs.count(&mMutex))
		g_mutexs[&mMutex] += 1;
	else
		g_mutexs[&mMutex] = 1;
	if (g_mutexs[&mMutex] > 1) {
		std::cout << "DEADLOCK" << std::endl;
		Sleep(1000);
	}
	mMutex->lock();
}

ScopedLock::~ScopedLock(void) {
	g_mutexs[&mMutex] -= 1;
	mMutex->unlock();
}
