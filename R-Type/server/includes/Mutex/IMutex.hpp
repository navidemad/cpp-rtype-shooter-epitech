#pragma once

class IMutex {

	// ctor dtor
	public:
        virtual ~IMutex(void) = default;

	// interface implementation
	public:
		virtual void	lock(void) = 0;
		virtual void	unlock(void) = 0;
		virtual void	trylock(void) = 0;
		virtual void	*getMutex(void) = 0;

};
