#pragma once

#include "IMutex.hpp"
#include "NoCopyable.hpp"

#include <memory>

#define Scopedlock(mutex) ScopedLock scoped_lock(mutex, __FUNCTION__, __FILE__, __LINE__)

class ScopedLock : public NoCopyable {

	// ctor dtor
	public:
		explicit ScopedLock(std::shared_ptr<IMutex> mutex, const char* callerFunctionName, const char* callerFile, const unsigned long callerLine);
		~ScopedLock(void);

	// check deadlock
	public:
		bool find(void *addr) ;

	// attributes
	private:
        std::shared_ptr<IMutex> mMutex;

};
