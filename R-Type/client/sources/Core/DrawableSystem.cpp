#include "Core/DrawableSystem.hpp"
#include "Engine/ComponentType.h"
#include "Engine/Entity.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Drawable.hpp"
#include "Engine/ECSManager.hpp"
#include "GUI/IGraphic.hpp"
#include "RTypeClient.hpp"

#include <iostream>
DrawableSystem::DrawableSystem()
{
	setComponentNeeded(ComponentType::DRAWABLE);
	setComponentNeeded(ComponentType::MOVABLE);
}

void	DrawableSystem::process(Entity &entity, float /* */)
{
	Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));
	Drawable *sprite = static_cast<Drawable *>(entity.getSpecificComponent(ComponentType::DRAWABLE));

	entity.getEntityManager()->getClient()->getGui()->drawSprite(sprite->getName(), 0, pos->getX(), pos->getY());
}