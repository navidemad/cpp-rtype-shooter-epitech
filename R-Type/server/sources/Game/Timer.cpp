#include "Timer.hpp"

Timer::Timer(void) : mStartTime(std::clock()), mPingTime(mStartTime) {

}

Timer::~Timer(void) {

}

void Timer::reset(void) {
	mStartTime = std::clock();
	mPingTime = mStartTime;
}

bool Timer::ping(void) {
	if (double(std::clock() - mPingTime) / double(CLOCKS_PER_SEC) > 5.0)
	{
		mPingTime = std::clock();
		return true;
	}
	return false;		
}

double Timer::frame() const {
    return (double(std::clock() - mStartTime) / double(CLOCKS_PER_SEC));
}