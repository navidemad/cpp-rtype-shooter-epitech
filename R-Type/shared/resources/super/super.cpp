#include <cmath>
#include <cstdlib>
#include "super.hpp"

std::string         Super::getName(void) const {
    return "super";
}

float               Super::getHeight(void) const {
    return 50.f;
}

float               Super::getWidth(void) const {
    return 50.f;
}

short               Super::getLife(void) const {
	return 10;
}

float               Super::getMoveSpeed(void) const {
    return 1.0f;
}

float               Super::getFireDeltaTime(void) const {
    return 0.3f;
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
