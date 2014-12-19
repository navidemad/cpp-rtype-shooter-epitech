#include <cstdlib>
#include <iostream>
#include "Monster.hpp"

Monster::Monster(void) : IResource("monster"), mSpeed(0.42) {
}

Monster::~Monster(void) {

}

double Monster::getSpeed(void) const {
	return mSpeed;
}

extern "C"
{
    MYLIB_EXPORT IResource* entry_point(void)
    {
        return reinterpret_cast<IResource*>(new Monster);
    }
}
