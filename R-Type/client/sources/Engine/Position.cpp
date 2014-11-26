#include "Engine/Compenent/Position.hpp"
#include "Engine/ComponentType.h"

Position::Position(float x, float y)
: Component(ComponentType::MOVABLE), mX(x), mY(y)
{

}

Position::~Position()
{

}

const float	Position::getX() const
{
	return mX;
}

const float	Position::getY() const
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