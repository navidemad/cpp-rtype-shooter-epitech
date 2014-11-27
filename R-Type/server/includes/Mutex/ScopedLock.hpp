#pragma once

#include "IMutex.hpp"
#include "NoCopyable.hpp"

#include <memory>

class ScopedLock : public NoCopyable {

	// ctor dtor
	public:
		explicit ScopedLock(std::shared_ptr<IMutex> mutex);
		~ScopedLock(void);

	// attributes
	private:
        std::shared_ptr<IMutex> mMutex;

};
