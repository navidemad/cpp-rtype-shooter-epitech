#include <cmath>
#include <cstdlib>
#include "bullet.hpp"

std::string             Bullet::getName(void) const {
    return "bullet";
}

short                  Bullet::getHeight(void) const {
    return 33;
}

short                  Bullet::getWidth(void) const {
    return 34;
}

short                     Bullet::getLife(void) const {
    return 1;
}

double 			        Bullet::getMoveSpeed(void) const {
    return 0.6;
}

double                  Bullet::getFireDeltaTime(void) const {
    return 0.8;
}

IResource::Type         Bullet::getType(void) const {
    return IResource::Type::BULLET;
}

IResource::Vec2         Bullet::move(double) const {
    return IResource::Vec2(50, 0);
}

IResource::Vec2         Bullet::fire(double) const {
    return IResource::Vec2(0, 0);
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Bullet);
    }
}
