#include "Core/VelocitySystem.hpp"
#include "Engine/ComponentType.h"
#include "Engine/Compenent/Velocity.hpp"
#include "Engine/Compenent/Position.hpp"

VelocitySystem::VelocitySystem()
{
	setComponentNeeded(ComponentType::VELOCITY);
	setComponentNeeded(ComponentType::MOVABLE);
}

VelocitySystem::~VelocitySystem()
{

}
#include <iostream>
void		VelocitySystem::process(Entity &entity, uint32_t delta)
{
	Velocity *velocity = static_cast<Velocity *>(entity.getSpecificComponent(ComponentType::VELOCITY));
	Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));

	velocity->addTimeElapsed(delta);
	if (velocity->getTime() != 0 && velocity->hasTimeElapsed())
	{
		pos->setX(pos->getX() + (velocity->getX() * (velocity->getTimeElapsed() / velocity->getTime())));
		pos->setY(pos->getY() + (velocity->getY() * (velocity->getTimeElapsed() / velocity->getTime())));
		velocity->reset();
	}
}