#pragma once

#include "../Component.hpp"
#include "../ComponentType.h"

class Position : public Component
{
	// ctor - dtor
	public:
		Position(int, int);
		~Position();

	// coplien form
	private:
		Position(Position const &) : Component(ComponentType::MOVABLE), mX(0), mY(0) {}
		Position const	&operator=(Position const &) { return *this; }

	public:
		inline const int	getX() const;
		inline const int	getY() const;
		inline void			setX(int);
		inline void			setY(int);

	private:
		int			mX;
		int			mY;
};
