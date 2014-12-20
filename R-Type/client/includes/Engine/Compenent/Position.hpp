#pragma once

#include "../Component.hpp"
#include "../ComponentType.h"
#include "NoCopyable.hpp"

class Position : public NoCopyable, public Component
{
	// ctor - dtor
	public:
		Position(float, float);
		~Position();

	public:
        double		getX() const;
        double		getY() const;
        void			setX(double);
        void			setY(double);

	private:
        double			mX;
        double			mY;
};
