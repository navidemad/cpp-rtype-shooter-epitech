#pragma once

#include "IMutex.hpp"
#include <memory>

class ScopedLock {

	// ctor dtor
	public:
		explicit ScopedLock(std::shared_ptr<IMutex> mutex);
		~ScopedLock(void);

	// copy / move operators
	public:
		ScopedLock(const ScopedLock &) = delete;
		ScopedLock(ScopedLock &&) = delete;
		const ScopedLock &operator=(const ScopedLock &) = delete;
		const ScopedLock &operator=(ScopedLock &&) = delete;

	// attributes
	private:
        std::shared_ptr<IMutex> mMutex;

};
