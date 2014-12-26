#include <cmath>
#include <cstdlib>
#include "melee.hpp"

std::string             Melee::getName(void) const {
    return "melee";
}

short                  Melee::getHeight(void) const {
    return 50;
}

short                  Melee::getWidth(void) const {
    return 50;
}

short                  Melee::getLife(void) const {
	return 1;
}

double 			        Melee::getMoveSpeed(void) const {
    return 0.6;
}

double                  Melee::getFireDeltaTime(void) const {
    return 0.8;
}

IResource::Type         Melee::getType(void) const {
    return IResource::Type::MELEE;
}

IResource::Vec2         Melee::move(double) const {
	return IResource::Vec2(-50, 0);
}

IResource::Vec2         Melee::fire(double) const {
	return IResource::Vec2(0, 0);
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Melee);
    }
}
