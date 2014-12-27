#include "Engine/Compenent/Position.hpp"
#include "Engine/ComponentType.h"

Position::Position(short x, short y)
: Component(ComponentType::MOVABLE), mX(x), mY(y)
{

}

Position::~Position()
{

}

float	Position::getX() const
{
	return mX;
}

float	Position::getY() const
{
	return mY;
}

void		Position::setX(float x)
{
	mX = x;
}

void		Position::setY(float y)
{
	mY = y;
}