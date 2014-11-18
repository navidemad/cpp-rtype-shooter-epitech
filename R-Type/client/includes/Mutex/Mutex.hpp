#pragma once

#include "IMutex.hpp"
#include <qmutex.h>

class Mutex : public IMutex {

	// ctor - dtor
	public:
		Mutex(void) {}
		~Mutex(void) {}

	// handle mutex
	public:
		void	lock(void);
		bool	tryLock(int milliseconds = -1);
		void	unlock(void);

	// attributes
	private:
		QMutex	mQMutex;

};
