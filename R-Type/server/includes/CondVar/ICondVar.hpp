#pragma once

#include <memory>
#include "IMutex.hpp"

class ICondVar {

	// ctor dtor
	public:
		virtual ~ICondVar(void) {}

	// interface implementation
	public:
        virtual void wait(std::shared_ptr<IMutex>) = 0;
		virtual void signal(void) = 0;
		virtual void broadcast(void) = 0;

};
