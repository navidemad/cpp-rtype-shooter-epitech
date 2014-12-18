#include "Timer.hpp"

Timer::Timer(void) : mStartTime(std::clock()) {

}

Timer::~Timer(void) {

}

void Timer::reset(void) {
	mStartTime = std::clock();
}

double Timer::frame() const {
    return (double(std::clock() - mStartTime) / double(CLOCKS_PER_SEC));
}