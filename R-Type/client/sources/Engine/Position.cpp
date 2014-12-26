#include "Engine/Compenent/Position.hpp"
#include "Engine/ComponentType.h"

Position::Position(short x, short y)
: Component(ComponentType::MOVABLE), mX(x), mY(y)
{

}

Position::~Position()
{

}

short	Position::getX() const
{
	return mX;
}

short	Position::getY() const
{
	return mY;
}

void		Position::setX(short x)
{
	mX = x;
}

void		Position::setY(short y)
{
	mY = y;
}