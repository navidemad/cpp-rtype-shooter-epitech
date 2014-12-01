#include "Core/ButtonSystem.hpp"
#include "Engine/ComponentType.h"
#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "RTypeClient.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Cursor.hpp"
#include "Engine/Compenent/Button.hpp"

ButtonSystem::ButtonSystem()
{
	mTimeElapsed = 0;
	setComponentNeeded(ComponentType::CURSOR);
	setComponentNeeded(ComponentType::MOVABLE);
}

ButtonSystem::~ButtonSystem()
{

}

bool		ButtonSystem::hasTimeElapsed() const
{
	return mTimeElapsed > 100;
}

void		ButtonSystem::process(Entity &entity, uint32_t delta)
{
	Position *pos = static_cast<Position *>(entity.getSpecificComponent(ComponentType::MOVABLE));
	Cursor *button = static_cast<Cursor *>(entity.getSpecificComponent(ComponentType::CURSOR));
	 
	mTimeElapsed += delta;

	{
		Entity &entityCiblate = entity.getEntityManager()->getEntity(button->getIdEntity());

		Button	*button = static_cast<Button *>(entityCiblate.getSpecificComponent(ComponentType::BUTTON));
		button->process(entityCiblate, delta);
	}

	if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("down"))
	{
		entity.getEntityManager()->getClient()->getGui()->playSound("change_option");

		mTimeElapsed = 0;
		button->next();
	}
	else if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("up"))
	{
		entity.getEntityManager()->getClient()->getGui()->playSound("change_option");

		mTimeElapsed = 0;
		button->prev();
	}
	
	Entity &entityCiblate = entity.getEntityManager()->getEntity(button->getIdEntity());

	Position	*newPos = static_cast<Position *>(entityCiblate.getSpecificComponent(ComponentType::MOVABLE));
	pos->setY(newPos->getY() + 30);

}