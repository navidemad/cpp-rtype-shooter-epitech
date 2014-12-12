#include "Core/ButtonGameSystem.hpp"
#include "Engine/ComponentType.h"
#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "RTypeClient.hpp"
#include "Engine/Compenent/Position.hpp"
#include "Engine/Compenent/Cursor.hpp"
#include "Engine/Compenent/Button.hpp"

ButtonGameSystem::ButtonGameSystem()
{
	mTimeElapsed = 0;
	setComponentNeeded(ComponentType::CURSOR);
	setComponentNeeded(ComponentType::MOVABLE);
}

ButtonGameSystem::~ButtonGameSystem()
{

}

bool		ButtonGameSystem::hasTimeElapsed() const
{
	return mTimeElapsed / 1000 > 100;
}

void		ButtonGameSystem::process(Entity &entity, uint32_t delta)
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
		if (button->next())
		{
			entity.getEntityManager()->getClient()->getGui()->playSound("change_option");
			mTimeElapsed = 0;
		}
	}

	else if (hasTimeElapsed() && entity.getEntityManager()->getClient()->getGui()->isPressed("up"))
	{
		if (button->prev())
		{
			entity.getEntityManager()->getClient()->getGui()->playSound("change_option");
			mTimeElapsed = 0;
		}
	}

	Entity &entityCiblate = entity.getEntityManager()->getEntity(button->getIdEntity());

	Position	*newPos = static_cast<Position *>(entityCiblate.getSpecificComponent(ComponentType::MOVABLE));
	pos->setY(newPos->getY() + 30);

}