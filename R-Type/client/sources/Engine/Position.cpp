#include "Engine/Compenent/Position.hpp"
#include "Engine/ComponentType.h"

Position::Position(float x, float y)
: Component(ComponentType::MOVABLE), mX(x), mY(y)
{

}

Position::~Position()
{

}

double	Position::getX() const
{
	return mX;
}

double	Position::getY() const
{
	return mY;
}

void		Position::setX(double x)
{
	mX = x;
}

void		Position::setY(double y)
{
	mY = y;
}