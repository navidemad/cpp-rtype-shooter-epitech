#pragma once

#include "../Component.hpp"
#include "../ComponentType.h"

class Velocity : public Component
{
	// ctor - dtor
	public:
		Velocity(unsigned int, unsigned int, unsigned int);
		~Velocity();

	// coplien form
	private:
		Velocity(Velocity const &) : Component(ComponentType::MOVABLE) {}
		Velocity const	&operator=(Velocity const &) { return *this; }

	public:
		unsigned int	getX() const;
		unsigned int	getY() const;
		unsigned int	getTime() const;

	public:
		unsigned int	mX;
		unsigned int	mY;
		unsigned int	mTime;
};
