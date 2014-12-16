#include "Engine/Compenent/Velocity.hpp"
#include "Engine/ComponentType.h"

Velocity::Velocity(int x, int y, unsigned int time)
: Component(ComponentType::VELOCITY), mX(x), mY(y), mTime(time)
{

}

Velocity::~Velocity()
{

}

int	Velocity::getX() const
{
	return mX;
}

int	Velocity::getY() const
{
	return mY;
}

unsigned int	Velocity::getTime() const
{
	return mTime;
}
