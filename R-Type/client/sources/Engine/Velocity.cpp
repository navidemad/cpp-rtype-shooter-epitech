#include "Engine/Compenent/Velocity.hpp"
#include "Engine/ComponentType.h"

Velocity::Velocity(unsigned int x, unsigned int y, unsigned int time)
: Component(ComponentType::VELOCITY), mX(x), mY(y), mTime(time)
{

}

Velocity::~Velocity()
{

}

unsigned int	Velocity::getX() const
{
	return mX;
}

unsigned int	Velocity::getY() const
{
	return mY;
}

unsigned int	Velocity::getTime() const
{
	return mTime;
}
