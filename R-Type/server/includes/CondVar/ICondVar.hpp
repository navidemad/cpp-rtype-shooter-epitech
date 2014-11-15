#pragma once

#include "IMutex.hpp"

class ICondVar {

	// ctor dtor
	public:
		virtual ~ICondVar(void) {}

	// interface implementation
	public:
		virtual void wait(IMutex *) = 0;
		virtual void signal(void) = 0;
		virtual void broadcast(void) = 0;

};
