#pragma once

class IMutex {

	// ctor dtor
	public:
		virtual ~IMutex(void) {}

	// interface implementation
	public:
		virtual void	lock(void) = 0;
		virtual void	unlock(void) = 0;
		virtual void	trylock(void) = 0;

};
