#include "Gameplay/Gameplay.hpp"
#include "Engine/ComponentType.h"

Gameplay::Gameplay(ComponentType::Type type) : Component(type) { }

Fire::Fire() : Gameplay(ComponentType::FIRE) { }
Fire::~Fire() { }

Up::Up() : Gameplay(ComponentType::UP) { }
Up::~Up() { }

Down::Down() : Gameplay(ComponentType::DOWN) { }
Down::~Down() { }

Left::Left() : Gameplay(ComponentType::LEFT) { }
Left::~Left() { }

Right::Right() : Gameplay(ComponentType::RIGHT) { }
Right::~Right() { }
