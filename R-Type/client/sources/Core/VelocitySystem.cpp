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

void		VelocitySystem::process(Entity &entity, uint32_t delta)
{
	Velocity *velocity = static_cast<Velocity *>(entity.getSpecificComponent(ComponentType::VELOCITY));
	Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));

	if (velocity->getTime() != 0)
	{
		pos->setX(pos->getX() - (velocity->getX() * (delta / static_cast<float>(velocity->getTime()))));
		pos->setY(pos->getY() - (velocity->getY() * (delta / static_cast<float>(velocity->getTime()))));
	}
}