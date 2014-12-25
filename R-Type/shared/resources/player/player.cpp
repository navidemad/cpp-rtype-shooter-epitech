#include <cmath>
#include <cstdlib>
#include "player.hpp"

std::string             Player::getName(void) const {
    return "player";
}

double                  Player::getHeight(void) const {
    return 0.025; // 20px sprite sur une hauteur fenetre de 800 sa fait cette valeur
}

double                  Player::getWidth(void) const {
    return 0.025; // 20px sprite sur une hauteur fenetre de 800 sa fait cette valeur
}

int                     Player::getLife(void) const {
	return 4;
}

double 			        Player::getMoveSpeed(void) const {
    return 0.5;
}

double                  Player::getFireDeltaTime(void) const {
    return 0.8;
}

IResource::Type         Player::getType(void) const {
    return IResource::Type::PLAYER;
}

IResource::Vec2         Player::move(double deltaTime) const {
	return IResource::Vec2(0., 0.);
}

IResource::Vec2         Player::fire(double) const {
	return IResource::Vec2(0., 0.);
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return dynamic_cast<IResource*>(new Player);
    }
}
