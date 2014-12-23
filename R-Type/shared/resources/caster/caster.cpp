#include <cmath>
#include <cstdlib>
#include "caster.hpp"

std::string             Caster::getName(void) const {
    return "caster";
}

double                  Caster::getHeight(void) const {
    return 0.025; // 20px sprite sur une hauteur fenetre de 800 sa fait cette valeur
}

double                  Caster::getWidth(void) const {
    return 0.025; // 20px sprite sur une hauteur fenetre de 800 sa fait cette valeur
}

int                     Caster::getLife(void) const {
	return 2;
}

double 			        Caster::getMoveSpeed(void) const {
	return .42;
}

double                  Caster::getFireSpeed(void) const {
	return .5;
}

IResource::Type         Caster::getType(void) const {
    return static_cast<IResource::Type>(IResource::Type::MONSTER | IResource::Type::CASTER | IResource::Type::COLLIDE);
}

IResource::Vec2         Caster::move(double deltaTime) const {
	return IResource::Vec2(-50., ((static_cast<int>(std::round(deltaTime)) % 2) * 2 - 1) * 100.);
}

IResource::Vec2         Caster::fire(double) const {
	return IResource::Vec2(-150., std::rand() % 100 - 60);
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Caster);
    }
}
