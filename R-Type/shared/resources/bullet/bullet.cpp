#include <cmath>
#include <cstdlib>
#include "bullet.hpp"

std::string         Bullet::getName(void) const {
    return "bullet";
}

float               Bullet::getHeight(void) const {
    return 33.f;
}

float               Bullet::getWidth(void) const {
    return 34.f;
}

short               Bullet::getLife(void) const {
    return 1;
}

float               Bullet::getMoveSpeed(void) const {
    return 2.0f;
}

float               Bullet::getFireDeltaTime(void) const {
    return 0.0f;
}

IResource::Type     Bullet::getType(void) const {
    return IResource::Type::BULLET;
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Bullet);
    }
}
