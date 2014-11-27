#include "Core/ButtonSystem.hpp"
#include "Engine/ComponentType.h"
#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "RTypeClient.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Cursor.hpp"

ButtonSystem::ButtonSystem()
{
	mTimeElapsed = 0;
	setComponentNeeded(ComponentType::CURSOR);
	setComponentNeeded(ComponentType::MOVABLE);
}

ButtonSystem::~ButtonSystem()
{

}
#include <iostream>
void		ButtonSystem::process(Entity &entity, float delta)
{
	Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));
	Cursor *button = static_cast<Cursor *>(entity.getSpecificComponent(ComponentType::CURSOR));
	 
	mTimeElapsed += delta;
	if (mTimeElapsed > 0.1 && entity.getEntityManager()->getClient()->getGui()->isPressed("down"))
	{
		mTimeElapsed = 0.;
		button->next();
	}
	else if (mTimeElapsed > 0.1 && entity.getEntityManager()->getClient()->getGui()->isPressed("up"))
	{
		mTimeElapsed = 0.;
		button->prev();
	}
	
	Entity &entityCiblate = entity.getEntityManager()->getEntity(button->getIdEntity());

	Position	*newPos = static_cast<Position *>(entityCiblate.getSpecificComponent(ComponentType::MOVABLE));
	pos->setY(newPos->getY() + 50);

}