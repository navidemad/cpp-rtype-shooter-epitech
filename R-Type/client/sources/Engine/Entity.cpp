#include <algorithm>
#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "Engine/Component.hpp"
#include <iostream>
Entity::Entity(const unsigned int id, ECSManager *entityManager)
: mId(id), mEntityManager(entityManager)
{
}

Entity::~Entity()
{

}

unsigned int	Entity::getId() const
{
	return mId;
}

bool					Entity::addComponent(Component *component)
{
	return mEntityManager->addComponent(mId, component);
}

Component				*Entity::getSpecificComponent(ComponentType::Type searchType)
{
    auto search = [&](const Component *currentCompenent)
	{
		if (!this->getEntityManager()->isEntityAlive(this->getId()))
			return false;
		return searchType == currentCompenent->getComponentId();
	};

    auto it = std::find_if(mEntityManager->getComponent(mId).begin(), mEntityManager->getComponent(mId).end(), search);

	if (it == mEntityManager->getComponent(mId).end())
        throw ComponentNotFound();

	return *it;
}

std::bitset<ComponentType::LIMIT>	Entity::getComponentBit() const
{
	const std::list<Component *> list = getComponent();
	std::bitset<ComponentType::LIMIT>	bitset;

	for (const Component *current : list)
	{
		bitset.set(current->getComponentId(), 1);
	}

	return bitset;
}

const std::list<Component *>			&Entity::getComponent() const
{
	return mEntityManager->getComponent(mId);
}
