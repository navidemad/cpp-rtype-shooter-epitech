#include <cmath>
#include <cstdlib>
#include "super.hpp"

std::string             Super::getName(void) const {
    return "super";
}

short                  Super::getHeight(void) const {
    return 50;
}

short                  Super::getWidth(void) const {
    return 50;
}

short                     Super::getLife(void) const {
	return 10;
}

double 			        Super::getMoveSpeed(void) const {
    return 0.6;
}

double                  Super::getFireDeltaTime(void) const {
    return 0.8;
}

IResource::Type         Super::getType(void) const {
    return IResource::Type::SUPER;
}

IResource::Vec2         Super::move(double deltaTime) const {
    return IResource::Vec2((deltaTime > 3 ? 64 : 0), ((static_cast<int>(std::round(deltaTime / 2)) % 2) * 2 - 1) * 150);
}

IResource::Vec2         Super::fire(double) const {
	return IResource::Vec2(-300, 0);
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Super);
    }
}
