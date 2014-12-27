#include <cmath>
#include <cstdlib>
#include "melee.hpp"

std::string         Melee::getName(void) const {
    return "melee";
}

float               Melee::getHeight(void) const {
    return 30.f;
}

float               Melee::getWidth(void) const {
    return 33.f;
}

short               Melee::getLife(void) const {
	return 5;
}

float               Melee::getMoveSpeed(void) const {
    return 0.42f;
}

float               Melee::getFireDeltaTime(void) const {
    return 0.0f;
}

IResource::Type     Melee::getType(void) const {
    return IResource::Type::MELEE;
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Melee);
    }
}
