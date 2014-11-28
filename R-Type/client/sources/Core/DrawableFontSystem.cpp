#include "Core/DrawableFontSystem.hpp"
#include "Engine/ComponentType.h"
#include "Engine/Entity.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Font.hpp"
#include "Engine/ECSManager.hpp"
#include "GUI/IGraphic.hpp"
#include "RTypeClient.hpp"

#include <iostream>
DrawableFontSystem::DrawableFontSystem()
{
	setComponentNeeded(ComponentType::FONT);
	setComponentNeeded(ComponentType::MOVABLE);
}

void	DrawableFontSystem::process(Entity &entity, uint32_t /* */)
{
	Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));
	Font *sprite = static_cast<Font *>(entity.getSpecificComponent(ComponentType::FONT));

	entity.getEntityManager()->getClient()->getGui()->drawFont(sprite->getFont(), sprite->getText(), pos->getX(), pos->getY(), 100);
}