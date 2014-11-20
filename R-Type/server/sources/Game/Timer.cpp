#include "Timer.hpp"

Timer::Timer(void) : mStart(std::clock()) {

}

Timer::~Timer(void) {

}

void Timer::restart() {
    mStart = std::clock();
}

double Timer::frame() const {
    return (double(std::clock() - mStart) / double(CLOCKS_PER_SEC));
}