#include "Gameplay/Gameplay.hpp"
#include "Engine/ComponentType.h"

Gameplay::Gameplay(ComponentType::Type type, uint32_t cycle = 0) : Component(type), mTimeElapsed(0), mCycle(cycle) { }

bool	Gameplay::hasTimeElapsed() const
{
	return mTimeElapsed > mCycle;
}


void	Gameplay::resetTimer()
{
	mTimeElapsed = 0;
}

void	Gameplay::addDelta(uint32_t delta)
{
	mTimeElapsed += delta;
}

Fire::Fire() : Gameplay(ComponentType::FIRE, 200) { }
Fire::~Fire() { }

Up::Up() : Gameplay(ComponentType::UP) { }
Up::~Up() { }

Down::Down() : Gameplay(ComponentType::DOWN) { }
Down::~Down() { }

Left::Left() : Gameplay(ComponentType::LEFT) { }
Left::~Left() { }

Right::Right() : Gameplay(ComponentType::RIGHT) { }
Right::~Right() { }