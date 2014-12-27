#include "Engine/Compenent/Velocity.hpp"
#include "Engine/ComponentType.h"

Velocity::Velocity(float x, float y, unsigned int time)
: Component(ComponentType::VELOCITY), mX(x), mY(y), mTime(time), mTimeElapsed(0)
{

}

Velocity::~Velocity()
{

}

float	Velocity::getX() const
{
	return mX;
}

float	Velocity::getY() const
{
	return mY;
}

unsigned int	Velocity::getTime() const
{
	return mTime;
}

void	Velocity::addTimeElapsed(unsigned int timeElapsed)
{
	mTimeElapsed += timeElapsed;
}

bool	Velocity::hasTimeElapsed() const
{
	return mTimeElapsed > mTime;
}

unsigned int	Velocity::getTimeElapsed() const
{
	return mTimeElapsed;
}

void	Velocity::reset()
{
	mTimeElapsed = mTimeElapsed - ((mTimeElapsed / mTime) * mTime);
}