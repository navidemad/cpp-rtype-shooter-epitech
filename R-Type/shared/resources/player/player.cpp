#include <cmath>
#include <cstdlib>
#include "player.hpp"

std::string         Player::getName(void) const {
    return "player";
}

float               Player::getHeight(void) const {
    return 21.f;
}

float               Player::getWidth(void) const {
    return 33.f;
}

short               Player::getLife(void) const {
	return 4;
}

float               Player::getMoveSpeed(void) const {
    return 4.0f;
}

float               Player::getFireDeltaTime(void) const {
    return 0.2f;
}

IResource::Type     Player::getType(void) const {
    return IResource::Type::PLAYER;
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Player);
    }
}
