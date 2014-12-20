#pragma once

#include "../Component.hpp"
#include "../ComponentType.h"

class Position : public Component
{
	// ctor - dtor
	public:
		Position(float, float);
		~Position();

	// coplien form
	private:
		Position(Position const &) : Component(ComponentType::MOVABLE), mX(0), mY(0) {}
		Position const	&operator=(Position const &) { return *this; }

	public:
        double		getX() const;
        double		getY() const;
        void			setX(double);
        void			setY(double);

	private:
        double			mX;
        double			mY;
};
