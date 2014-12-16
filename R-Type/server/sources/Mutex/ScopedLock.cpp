#include "ScopedLock.hpp"

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <unordered_map>
#include <thread>
#include <unistd.h>

static std::unordered_map<std::thread::id, void*> mutex_address;

ScopedLock::ScopedLock(std::shared_ptr<IMutex> mutex, const char* callerFunctionName, const char* callerFile, const unsigned long callerLine) : mMutex(mutex) {
	/*
	if (this->find(&*mMutex) 
		&& std::string(callerFile) != "sources/Thread/ThreadPool.cpp"
		&& std::string(callerFile) != "sources/Network/UnixUdpClient.cpp"
		)
	{
		std::cout << std::endl << "[DEADLOCK] " << callerFunctionName << ": Called from " << callerFile << ":" << callerLine << std::endl;
		#ifdef __OS_WINDOWS__
			Sleep(1000);
		#else
			sleep(1);
		#endif
	}
	mutex_address.insert({std::this_thread::get_id(), &*mMutex});
	*/
	//if (std::string(callerFile) == "sources/Game/GamesManager.cpp" && std::string(callerFunctionName) != "getGames")
	//	std::cout << "avant GamesManager " << callerFunctionName << ": Called from " << callerFile << ":" << callerLine << std::endl;
	//else if (std::string(callerFile) == "sources/Game/Game.cpp")
	//	std::cout << "avant Game " << callerFunctionName << ": Called from " << callerFile << ":" << callerLine << std::endl;
	mMutex->lock();
	//if (std::string(callerFile) == "sources/Game/GamesManager.cpp" && std::string(callerFunctionName) != "getGames")
	//	std::cout << "apres GamesManager " << callerFunctionName << ": Called from " << callerFile << ":" << callerLine << std::endl << std::endl;
	//else if (std::string(callerFile) == "sources/Game/Game.cpp")
	//	std::cout << "apres Game " << callerFunctionName << ": Called from " << callerFile << ":" << callerLine << std::endl;
}

ScopedLock::~ScopedLock(void) {
	mMutex->unlock();
}

bool ScopedLock::find(void *addr)  {
	return (std::find_if(mutex_address.begin(), mutex_address.end(),  [&](const std::unordered_map<std::thread::id, void*>::value_type& p)
	{ return p.first == std::this_thread::get_id() && p.second == addr; }) != mutex_address.end());
}
