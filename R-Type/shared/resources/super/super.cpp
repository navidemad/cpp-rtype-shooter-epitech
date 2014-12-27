#include <cmath>
#include <cstdlib>
#include "super.hpp"

std::string         Super::getName(void) const {
    return "super";
}

float               Super::getHeight(void) const {
    return 53.f;
}

float               Super::getWidth(void) const {
    return 47.f;
}

short               Super::getLife(void) const {
	return 2;
}

float               Super::getMoveSpeed(void) const {
    return 0.8f;
}

float               Super::getFireDeltaTime(void) const {
    return 1.0f;
}

IResource::Type     Super::getType(void) const {
    return IResource::Type::SUPER;
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Super);
    }
}
