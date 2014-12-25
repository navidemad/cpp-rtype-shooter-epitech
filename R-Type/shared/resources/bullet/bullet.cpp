#include <cmath>
#include <cstdlib>
#include "bullet.hpp"

std::string             Bullet::getName(void) const {
    return "bullet";
}

double                  Bullet::getHeight(void) const {
    return 0.025; // 20px sprite sur une hauteur fenetre de 800 sa fait cette valeur
}

double                  Bullet::getWidth(void) const {
    return 0.025; // 20px sprite sur une hauteur fenetre de 800 sa fait cette valeur
}

int                     Bullet::getLife(void) const {
    return 1;
}

double 			        Bullet::getMoveSpeed(void) const {
    return 2.5;
}

double                  Bullet::getFireSpeed(void) const {
    return 0.;
}

IResource::Type         Bullet::getType(void) const {
    return IResource::Type::BULLET;
}

IResource::Vec2         Bullet::move(double) const {
    return IResource::Vec2(50., 0.);
}

IResource::Vec2         Bullet::fire(double) const {
    return IResource::Vec2(0., 0.);
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Bullet);
    }
}
