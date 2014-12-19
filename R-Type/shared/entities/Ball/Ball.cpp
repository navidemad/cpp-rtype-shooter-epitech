#include <cstdlib>
#include <iostream>
#include "Ball.hpp"

Ball::Ball(void) : IResource("ball"), mSpeed(0.42) {
}

Ball::~Ball(void) {

}

double Ball::getSpeed(void) const {
	return mSpeed;
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
		return reinterpret_cast<IResource*>(new Ball);
    }
}
