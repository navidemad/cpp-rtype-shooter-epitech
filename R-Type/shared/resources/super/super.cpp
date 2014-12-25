#include <cmath>
#include <cstdlib>
#include "super.hpp"

std::string             Super::getName(void) const {
    return "super";
}

double                  Super::getHeight(void) const {
    return 0.025; // 20px sprite sur une hauteur fenetre de 800 sa fait cette valeur
}

double                  Super::getWidth(void) const {
    return 0.025; // 20px sprite sur une hauteur fenetre de 800 sa fait cette valeur
}

int                     Super::getLife(void) const {
	return 10;
}

double 			        Super::getMoveSpeed(void) const {
    return 2.5;
}

double                  Super::getFireSpeed(void) const {
	return 1.;
}

IResource::Type         Super::getType(void) const {
    return IResource::Type::SUPER;
}

IResource::Vec2         Super::move(double deltaTime) const {
    return IResource::Vec2((deltaTime > 3 ? 64. : 0.), ((static_cast<int>(std::round(deltaTime / 2.)) % 2) * 2 - 1) * 150.);
}

IResource::Vec2         Super::fire(double) const {
	return IResource::Vec2(-300., 0.);
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Super);
    }
}
