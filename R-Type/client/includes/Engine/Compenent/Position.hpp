#pragma once

#include "../Component.hpp"
#include "../ComponentType.h"
#include "NoCopyable.hpp"

class Position : public NoCopyable, public Component
{
	// ctor - dtor
	public:
        Position(short, short);
		~Position();

	public:
        float			getX() const;
        float			getY() const;
        void			setX(float);
        void			setY(float);

	private:
        float			mX;
        float			mY;
};
