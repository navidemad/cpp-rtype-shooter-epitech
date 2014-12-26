#include <cmath>
#include <cstdlib>
#include "caster.hpp"

std::string             Caster::getName(void) const {
    return "caster";
}

short                  Caster::getHeight(void) const {
    return 50;
}

short                  Caster::getWidth(void) const {
    return 50;
}

short                     Caster::getLife(void) const {
	return 2;
}

double 			        Caster::getMoveSpeed(void) const {
    return 0.6;
}

double                  Caster::getFireDeltaTime(void) const {
    return 0.8;
}

IResource::Type         Caster::getType(void) const {
    return IResource::Type::CASTER;
}

IResource::Vec2         Caster::move(double deltaTime) const {
	return IResource::Vec2(-50, ((static_cast<int>(std::round(deltaTime)) % 2) * 2 - 1) * 100);
}

IResource::Vec2         Caster::fire(double) const {
	return IResource::Vec2(-150, std::rand() % 100 - 60);
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Caster);
    }
}
