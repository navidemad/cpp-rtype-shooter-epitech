#include "Engine/Entity.hpp"
#include "Engine/ECSManager.hpp"
#include "Engine/Component.hpp"

Entity::Entity(unsigned int id, ECSManager *entityManager)
: mId(id), mEntityManager(entityManager)
{

}

Entity::~Entity()
{

}

inline unsigned int	Entity::getId() const
{
	return mId;
}

inline bool					Entity::addComponent(Component *component)
{
	return mEntityManager->addComponent(mId, component);
}

inline std::bitset<ComponentType::LIMIT>	Entity::getComponentBit() const
{
	const std::list<Component *> list = getComponent();
	std::bitset<ComponentType::LIMIT>	bitset;

	for (const Component *current : list)
	{
		bitset.set(current->getComponentId(), 1);
	}

	return bitset;
}

inline const std::list<Component *>			&Entity::getComponent() const
{
	return mEntityManager->getComponent(mId);
}
