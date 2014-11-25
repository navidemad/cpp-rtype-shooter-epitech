#include "Engine/Compenent/Position.hpp"
#include "Engine/ComponentType.h"

Position::Position(int x, int y)
: Component(ComponentType::MOVABLE), mX(x), mY(y)
{

}

Position::~Position()
{

}

inline int	Position::getX() const
{
	return mX;
}

inline int	Position::getY() const
{
	return mY;
}

inline void		Position::setX(int x)
{
	mX = x;
}

inline void		Position::setY(int y)
{
	mY = y;
}