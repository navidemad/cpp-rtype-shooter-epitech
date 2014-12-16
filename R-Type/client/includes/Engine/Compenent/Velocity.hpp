#pragma once

#include "../Component.hpp"
#include "../ComponentType.h"

class Velocity : public Component
{
	// ctor - dtor
	public:
		Velocity(int, int, unsigned int);
		~Velocity();

	// coplien form
	private:
		Velocity(Velocity const &) : Component(ComponentType::MOVABLE) {}
		Velocity const	&operator=(Velocity const &) { return *this; }

	public:
		int	getX() const;
		int	getY() const;
		unsigned int	getTime() const;

	public:
		int	mX;
		int	mY;
		unsigned int	mTime;
};
