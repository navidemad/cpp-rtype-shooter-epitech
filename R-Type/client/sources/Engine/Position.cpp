#include "Engine/Compenent/Position.hpp"
#include "Engine/ComponentType.h"

Position::Position(float x, float y)
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