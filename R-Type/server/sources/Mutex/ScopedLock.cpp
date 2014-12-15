#include "ScopedLock.hpp"

#include <iostream>

std::vector<void*> ScopedLock::mutex_address;

ScopedLock::ScopedLock(std::shared_ptr<IMutex> mutex, const char* callerFunctionName, const char* callerFile, const unsigned long callerLine) : mMutex(mutex) {
	if (std::find(mutex_address.begin(), mutex_address.end(), &*mMutex) != mutex_address.end()) {
		std::cout << std::endl << "[DEADLOCK] " << callerFunctionName << ": Called from " << callerFile << ":" << callerLine << std::endl;
		std::terminate();
	}
	mutex_address.push_back(&*mMutex);
	mMutex->lock();
}

ScopedLock::~ScopedLock(void) {
	auto it = std::find(mutex_address.begin(), mutex_address.end(), &*mMutex);
	if(it != mutex_address.end())
	    mutex_address.erase(it);
	mMutex->unlock();
}
