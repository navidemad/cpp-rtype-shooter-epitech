#include <cmath>
#include <cstdlib>
#include "caster.hpp"

std::string         Caster::getName(void) const {
    return "caster";
}

float               Caster::getHeight(void) const {
    return 50.f;
}

float               Caster::getWidth(void) const {
    return 50.f;
}

short               Caster::getLife(void) const {
	return 1;
}

float               Caster::getMoveSpeed(void) const {
    return 0.8f;
}

float               Caster::getFireDeltaTime(void) const {
    return 1.00f;
}

IResource::Type     Caster::getType(void) const {
    return IResource::Type::CASTER;
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Caster);
    }
}
