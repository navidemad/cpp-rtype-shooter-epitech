#include <cstdlib>
#include <iostream>
#include "Player.hpp"

Player::Player(void) : IResource("player"), mSpeed(0.42) {
}

Player::~Player(void) {

}

double Player::getSpeed(void) const {
	return mSpeed;
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
		return reinterpret_cast<IResource*>(new Player);
    }
}
