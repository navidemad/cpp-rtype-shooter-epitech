#pragma once

#include "../Component.hpp"
#include "../ComponentType.h"
#include "NoCopyable.hpp"

class Velocity : public NoCopyable, public Component
{
	// ctor - dtor
	public:
		Velocity(float, float, unsigned int);
		~Velocity();

	public:
		float	getX() const;
		float	getY() const;
		unsigned int	getTime() const;

		bool			hasTimeElapsed() const;
		unsigned int	getTimeElapsed() const;
		void			addTimeElapsed(unsigned int);
		void			reset();

	public:
		float			mX;
		float			mY;
		unsigned int	mTime;
		unsigned int	mTimeElapsed;
};
