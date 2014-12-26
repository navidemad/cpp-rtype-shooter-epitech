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
        short		getX() const;
        short		getY() const;
        void			setX(short);
        void			setY(short);

	private:
        short			mX;
        short			mY;
};
