#pragma once

#include "IMutex.hpp"

class WindowsMutex : public IMutex {

	// ctor dtor
	public:
		WindowsMutex(void);
		~WindowsMutex(void);

	// copy / move operators
	public:
		WindowsMutex(const WindowsMutex &) = delete;
		WindowsMutex(const WindowsMutex &&) = delete;
		const WindowsMutex &operator=(const WindowsMutex &) = delete;
		const WindowsMutex &operator=(const WindowsMutex &&) = delete;

	// interface implementation
	public:
		void	lock(void) {}
		void	unlock(void) {}
		void	trylock(void) {}

};
