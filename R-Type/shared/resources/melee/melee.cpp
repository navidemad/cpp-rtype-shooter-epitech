#include <cmath>
#include <cstdlib>
#include "melee.hpp"

std::string             Melee::getName(void) const {
    return "melee";
}

double                  Melee::getHeight(void) const {
    return 0.025; // 20px sprite sur une hauteur fenetre de 800 sa fait cette valeur
}

double                  Melee::getWidth(void) const {
    return 0.025; // 20px sprite sur une hauteur fenetre de 800 sa fait cette valeur
}

int                     Melee::getLife(void) const {
	return 1;
}

double 			        Melee::getMoveSpeed(void) const {
    return 2.5;
}

double                  Melee::getFireSpeed(void) const {
	return 0.;
}

IResource::Type         Melee::getType(void) const {
    return IResource::Type::MELEE;
}

IResource::Vec2         Melee::move(double) const {
	return IResource::Vec2(-50., 0.);
}

IResource::Vec2         Melee::fire(double) const {
	return IResource::Vec2(0., 0.);
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Melee);
    }
}
