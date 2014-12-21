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
	auto search = [&](Component *currentCompenent)
	{
		return searchType == currentCompenent->getComponentId();
	};


	std::list<Component *>::const_iterator it = std::find_if(mEntityManager->getComponent(mId).begin(), mEntityManager->getComponent(mId).end(), search);

	ComponentNotFound exception;
	if (it == mEntityManager->getComponent(mId).end())
		throw exception;
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
