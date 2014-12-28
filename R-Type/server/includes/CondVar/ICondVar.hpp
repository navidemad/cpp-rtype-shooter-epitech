#pragma once

#include "IMutex.hpp"

#include <memory>

class ICondVar {

	// ctor dtor
	public:
        virtual ~ICondVar(void) = default;

	// interface implementation
	public:
        virtual void wait(const std::shared_ptr<IMutex> &) = 0;
		virtual void notifyOne(void) = 0;
        virtual void notifyAll(void) = 0;

};
