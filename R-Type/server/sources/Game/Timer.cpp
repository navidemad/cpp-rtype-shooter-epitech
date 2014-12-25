#include "Timer.hpp"

NGame::Timer::Timer(void) : mLast(std::chrono::high_resolution_clock::now()) {

}

long long NGame::Timer::getDelta(void) const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - mLast).count();
}

void NGame::Timer::restart(void) {
    mLast = std::chrono::high_resolution_clock::now();
}
