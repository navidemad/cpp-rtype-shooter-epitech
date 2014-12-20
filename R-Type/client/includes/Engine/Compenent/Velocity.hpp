#pragma once

#include "../Component.hpp"
#include "../ComponentType.h"
#include "NoCopyable.hpp"

class Velocity : public NoCopyable, public Component
{
	// ctor - dtor
	public:
		Velocity(int, int, unsigned int);
		~Velocity();

	public:
		int	getX() const;
		int	getY() const;
		unsigned int	getTime() const;

	public:
		int	mX;
		int	mY;
		unsigned int	mTime;
};
