#include "ScopedLock.hpp"

#include <iostream>
#include <cstdlib>

std::vector<void*> ScopedLock::mutex_address;

ScopedLock::ScopedLock(std::shared_ptr<IMutex> mutex, const char* callerFunctionName, const char* callerFile, const unsigned long callerLine) : mMutex(mutex) {
	if(std::find(mutex_address.begin(), mutex_address.end(), &*mMutex) != mutex_address.end()){
		std::cout << std::endl << "[DEADLOCK] " << callerFunctionName << ": Called from " << callerFile << ":" << callerLine << std::endl;
		std::exit(EXIT_FAILURE);
	}
	mutex_address.push_back(&*mMutex);
	mMutex->lock();
}

ScopedLock::~ScopedLock(void) {
	mutex_address.erase(std::remove_if(mutex_address.begin(), mutex_address.end(), [&](void* addr){return &*mMutex == addr; }));
	mMutex->unlock();
}
